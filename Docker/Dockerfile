FROM gitpod/workspace-full-vnc

USER root

RUN apt-get update \
    && apt-get install -y qt5-default \
    && apt-get clean && rm -rf /var/cache/apt/* && rm -rf /var/lib/apt/lists/* && rm -rf /tmp/*

RUN pip3 install --upgrade pip
RUN pip3 install conan

user gitpod
