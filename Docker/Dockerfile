FROM gitpod/workspace-full-vnc

USER root

RUN apt update && apt upgrade -y

RUN DEBIAN_FRONTEND=noninteractive apt install -y tzdata

RUN DEBIAN_FRONTEND=noninteractive apt install -y keyboard-configuration

RUN apt install -y qt5-default \
    qtbase5-dev \
    qt5-default qttools5-dev-tools qttools5-dev libqt5svg5-dev \
    libqt5help5 libqt5svg5-dev qt5-image-formats-plugins  \
    qtdeclarative5-dev qtdeclarative5-dev-tools \
    install -y locales locales-all \
    && apt-get clean && rm -rf /var/cache/apt/* && rm -rf /var/lib/apt/lists/* && rm -rf /tmp/*

ENV LC_ALL en_US.UTF-8

ENV LANG en_US.UTF-8

ENV LANGUAGE en_US.UTF-8


RUN pip3 install --upgrade pip
RUN pip3 install conan

user gitpod
