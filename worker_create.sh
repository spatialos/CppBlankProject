#! /bin/bash
set -e -u -x -o pipefail

# Usage: worker_create.sh <Managed|External> <NewWorkerName> <path/to/destination/project>

OLD_NAME=$1
NEW_NAME=$2
DEST_PROJECT_PATH=$3

if [ `uname` == 'Darwin' ]; then
    if [ -z `which gsed` ]; then
        echo "Sorry, GNU sed must be on your PATH as gsed for this script to work.
If you use homebrew try:
    brew install gnu-sed
"
        exit 1
    fi
    SED=gsed
else
    SED=sed
fi

# Copy worker project to destination
mkdir -p $DEST_PROJECT_PATH/workers/$NEW_NAME
if [ `uname` == 'Darwin' ]; then
    # non-GNU cp does not understand -T; achieve the equivalent effect by
    # appending a slash to the source dir.
    cp -r workers/$OLD_NAME/ $DEST_PROJECT_PATH/workers/$NEW_NAME
else
    cp -rT workers/$OLD_NAME $DEST_PROJECT_PATH/workers/$NEW_NAME
fi

# Copy CMakeLists for worker SDK and schema / generated code
mkdir -p $DEST_PROJECT_PATH/dependencies/
cp dependencies/CMakeLists.txt $DEST_PROJECT_PATH/dependencies/

cp schema/CMakeLists.txt $DEST_PROJECT_PATH/schema

# Remove blank component from schema CMakeLists.txt
$SED -i '/blank/d' $DEST_PROJECT_PATH/schema/CMakeLists.txt

# Ignore generated files from source control
cat <<EOT >> $DEST_PROJECT_PATH/.gitignore
dependencies/worker_sdk/

# Generated code from schema
generated_code/

# Cache from generated code and other metadata
.spatialos/
EOT

# Change to new worker directory
cd $DEST_PROJECT_PATH/workers/$NEW_NAME

# Rename worker configuration file
mv spatialos.$OLD_NAME.worker.json spatialos.$NEW_NAME.worker.json

# Find and replace in files (use double quotes to expand variables)
$SED -i "s/$OLD_NAME/$NEW_NAME/g" spatialos.$NEW_NAME.worker.json
$SED -i "s/$OLD_NAME/$NEW_NAME/g" CMakeLists.txt
$SED -i "s/$OLD_NAME/$NEW_NAME/g" build.json
$SED -i "s/$OLD_NAME/$NEW_NAME/g" src/startup.cc
