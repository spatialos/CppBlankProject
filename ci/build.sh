#!/usr/bin/env bash

set -e -u -x -o pipefail

cd "$(dirname "$0")/.."

if [[ -z ${BUILDKITE+x} ]]; then
  echo "This script is intended to run in CI only."
  exit 1
fi

SPATIALOS_TOOLBELT_VERSION="latest"

TOOLBELT_PLATFORM=""
SPATIAL_PLATFORM=""
SPATIAL_BINARY=""

# Setup platform specific environment variables.
if [[ "$(uname -s)" == "Linux" ]]; then
  TOOLBELT_PLATFORM="linux"
  SPATIAL_PLATFORM="linux"
  SPATIAL_BINARY="spatial"
elif [[ "$(uname -s)" == "Darwin" ]]; then
  TOOLBELT_PLATFORM="mac"
  SPATIAL_PLATFORM="macos"
  SPATIAL_BINARY="spatial"

  imp-tool-bootstrap subscribe \
    --use_gcs_oidc_auth=false \
    --gcs_credentials_type=auto \
    --tools=imp-tool
else
  TOOLBELT_PLATFORM="win"
  SPATIAL_PLATFORM="windows"
  SPATIAL_BINARY="spatial.exe"
fi

# Create temporary directories for the spatial binary and authentication token.
export AUTH_DIR="$(mktemp -d)"
export TOOLS_DIR="$(mktemp -d)"

# Retrieve the authentication token.
if [[ "$SPATIAL_PLATFORM" == "macos" ]]; then
  imp-vault read-key \
      --environment=production \
      --field=token \
      --key=secret/sync.v1/dev-workflow/production-buildkite/buildkite-agents/spatialos-service-account/ci/improbable/worker-blank-projects-ci-token \
      --vault_role=continuous-integration-production-improbable-iam \
      --write_to="${AUTH_DIR}/oauth2_refresh_token"
else
  imp-ci secrets read \
      --environment=production \
      --buildkite-org=improbable \
      --secret-type=spatialos-service-account \
      --secret-name=worker-blank-projects-ci-token \
      --field=token \
      --write-to="${AUTH_DIR}/oauth2_refresh_token"
fi

# Retrieve the spatial binary.
curl -Ls -o "${TOOLS_DIR}/${SPATIAL_BINARY}.tmp" "https://console.improbable.io/toolbelt/download/${SPATIALOS_TOOLBELT_VERSION}/${TOOLBELT_PLATFORM}" || exit 1
chmod +x "${TOOLS_DIR}/${SPATIAL_BINARY}.tmp"
mv "${TOOLS_DIR}/${SPATIAL_BINARY}.tmp" "${TOOLS_DIR}/${SPATIAL_BINARY}"

# Build
if [[ "$SPATIAL_PLATFORM" == "linux" ]]; then
  docker build \
    -t cpp_exampe_project_image \
    -f ci/Dockerfile \
    --build-arg USER_ID=$(id -u) \
    --build-arg GROUP_ID=$(id -g) \
    .
  docker run \
    --rm \
    --volume "${TOOLS_DIR}":/build/tools \
    --env TOOLS_DIR=/build/tools \
    --volume "${AUTH_DIR}":/build/auth \
    --env AUTH_DIR=/build/auth \
    --volume $(pwd):/code \
    --workdir /code \
    cpp_exampe_project_image \
    /bin/bash -c 'export PATH="/code/ci:${PATH}"; \
      spatial build --target '"$SPATIAL_PLATFORM"
else
  # Add the spatial wrapper script to the path.
  export PATH="$(pwd)/ci":"$PATH"
  spatial build --target $SPATIAL_PLATFORM
fi
