FROM gitpod/workspace-full-vnc

USER root

ENV DEBIAN_FRONTEND noninteractive

RUN apt-get update && apt-get upgrade -y \
    && apt-get install -y tzdata \
    && apt-get install -y keyboard-configuration \
    && apt-get install -y qt5-default qtbase5-dev \
    qt5-default qttools5-dev-tools qttools5-dev libqt5svg5-dev \
    libqt5help5 libqt5svg5-dev qt5-image-formats-plugins  \
    qtdeclarative5-dev qtdeclarative5-dev-tools \
    locales locales-all \
    doxygen

# install dependencies
RUN apt-get update \
    && apt-get install -y  matchbox twm

RUN apt-get clean && rm -rf /var/cache/apt/* && rm -rf /var/lib/apt/lists/* && rm -rf /tmp/*


RUN pip3 install --upgrade pip
RUN pip3 install conan

USER gitpod
