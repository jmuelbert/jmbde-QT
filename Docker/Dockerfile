FROM gitpod/workspace-full-vnc

USER root

RUN apt-get update \
    && apt-get install -y qt5-default \
    qtbase5-dev qttools5-dev \
    qttools5-dev-tools libqt5help5  qtdeclarative5-dev \
    qtdeclarative5-dev-tools qt5-image-formats-plugins \
    libqt5svg5-dev \
    && apt-get clean && rm -rf /var/cache/apt/* && rm -rf /var/lib/apt/lists/* && rm -rf /tmp/*

RUN pip3 install --upgrade pip
RUN pip3 install conan

user gitpod
