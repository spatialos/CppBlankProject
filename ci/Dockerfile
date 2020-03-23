FROM ubuntu:18.04

RUN apt-get update \
    && apt-get install -y \
        cmake \
        g++ \
        gcc \
    && rm -rf /var/lib/apt/lists/*

ARG USER_ID
ARG GROUP_ID

RUN addgroup --gid $GROUP_ID user \
    && adduser --disabled-password --uid $USER_ID --gid $GROUP_ID user
USER user
