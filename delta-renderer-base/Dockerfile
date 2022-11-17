FROM ubuntu:22.04
ENV DEBIAN_FRONTEND noninteractive

RUN apt-get update; apt-get install -y \
    build-essential ninja-build bison flex byacc cmake pkg-config libwayland-dev \
    python3 python3-pip wayland-protocols libx11-dev libxext-dev \
    wget libxcb-randr0-dev libxrandr-dev libpng-dev llvm-dev \
    && curl -fsSL https://deb.nodesource.com/setup_18.x | bash - && apt-get install -y nodejs \
    && rm -rf /var/lib/apt/lists/*

RUN ln -s /usr/bin/python3 /usr/bin/python && \
    pip3 install --upgrade pip && \
    pip3 install meson mako

ENV MESA_VER 22.2.4
RUN wget https://archive.mesa3d.org/mesa-$MESA_VER.tar.xz && \
    tar -xf mesa-$MESA_VER.tar.xz && \
    rm mesa-$MESA_VER.tar.xz && \
    cd mesa-$MESA_VER && mkdir build && meson --buildtype=release \
    -Dvulkan-drivers=[] \
    -Dgallium-drivers=swrast \
    -Dgallium-omx=disabled \
    -Dglx=xlib \
    -Dosmesa=true \
    build && \
    ninja -C build && \
    ninja -C build install && \
    rm -rf /mesa-$MESA_VER

ENV LD_LIBRARY_PATH=/usr/lib64:/usr/local/lib/x86_64-linux-gnu:$LD_LIBRARY_PATH \
    LIBGL_ALWAYS_SOFTWARE=true

ENV GLEW_VER 2.2.0
RUN wget https://github.com/nigels-com/glew/releases/download/glew-$GLEW_VER/glew-$GLEW_VER.tgz && \
    tar -xf glew-$GLEW_VER.tgz && \
    rm glew-$GLEW_VER.tgz && \
    cd glew-$GLEW_VER && cd auto && \
    make && \
    cd .. && \
    make SYSTEM=linux-osmesa && make install && make clean && \
    rm -rf /glew-$GLEW_VER
CMD ["/bin/bash", "-l"]
