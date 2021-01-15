FROM gitpod/workspace-full-vnc

RUN apt-get update -y \
    && DEBIAN_FRONTEND=noninteractive apt-get install -y \
        build-essential libfontconfig1 mesa-common-dev libglu1-mesa-dev qt5-default \
    && apt-get autoremove -y \
    && apt-get autoclean -y

ENV LC_ALL en_US.UTF-8

ENV LANG en_US.UTF-8

ENV LANGUAGE en_US.UTF-8


RUN pip3 install --upgrade pip
RUN pip3 install conan

user gitpod
