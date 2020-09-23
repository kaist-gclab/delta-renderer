# https://github.com/OpenSWR/docker-images/blob/master/ubuntu20.04/Dockerfile
# https://github.com/utensils/docker-opengl

FROM ubuntu:20.04 
ENV DEBIAN_FRONTEND noninteractive

RUN apt-get update && \
    apt-get install -y \
    vim git gcc g++ gdb doxygen wget sudo curl autoconf gettext xutils-dev \
    libdrm-dev m4 pkg-config libtool bison flex zlib1g-dev cmake libgl1-mesa-dev \
    python3 python3-pip freeglut3-dev libwaffle-dev waffle-utils \
    ghostscript environment-modules rsync ninja-build locales xvfb

RUN pip3 install --upgrade pip && \
    pip3 install mako lxml untangle six numpy meson

ENV LLVM_INSTALL_VER 10.0.0
RUN wget https://github.com/llvm/llvm-project/releases/download/llvmorg-$LLVM_INSTALL_VER/llvm-$LLVM_INSTALL_VER.src.tar.xz && \
    tar -xf llvm-$LLVM_INSTALL_VER.src.tar.xz && \
    rm llvm-$LLVM_INSTALL_VER.src.tar.xz && \
    cd llvm-$LLVM_INSTALL_VER.src && mkdir build && cd build && cmake .. \
    -G "Unix Makefiles" \
    -DCMAKE_BUILD_TYPE=Release \
    -DLLVM_TARGETS_TO_BUILD=X86 \
    -DLLVM_BUILD_LLVM_DYLIB=1 \
    -DLLVM_LINK_LLVM_DYLIB=1 \
    -DLLVM_ENABLE_RTTI=1 \
    && make install -j`nproc` \
    && rm -rf /llvm-$LLVM_INSTALL_VER.src

# set timezone
ENV TZ=Asia/Seoul
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/timezone

# set locale
RUN sed -i -e 's/# en_US.UTF-8 UTF-8/en_US.UTF-8 UTF-8/' /etc/locale.gen && \
    dpkg-reconfigure --frontend=noninteractive locales && \
    update-locale LANG=en_US.UTF-8
ENV LANG en_US.UTF-8

ENV MESA_VER 20.1.8
RUN wget https://archive.mesa3d.org/mesa-$MESA_VER.tar.xz && \
    tar -xf mesa-$MESA_VER.tar.xz && \
    rm mesa-$MESA_VER.tar.xz && \
    cd mesa-$MESA_VER && mkdir build && meson --buildtype=release \
    -Dglx=gallium-xlib \
    -Dvulkan-drivers= \
    -Ddri-drivers= \
    -Dgallium-drivers=swrast,swr \
    -Dplatforms=x11 \
    -Dgallium-omx=disabled \
    -Dosmesa=gallium \
    build && \
    ninja -C build && \
    ninja -C build install && \
    rm -rf /mesa-$MESA_VER

ENV LD_LIBRARY_PATH=/usr/local/lib/x86_64-linux-gnu:$LD_LIBRARY_PATH \
    GALLIUM_DRIVER=swr \
    LIBGL_ALWAYS_SOFTWARE=true

RUN ln -s /usr/bin/python3 /usr/bin/python && \
    ln -s /usr/bin/pip3 /usr/bin/pip

ENV GLEW_VER 2.1.0
RUN wget https://github.com/nigels-com/glew/releases/download/glew-$GLEW_VER/glew-$GLEW_VER.tgz && \
    tar -xf glew-$GLEW_VER.tgz && \
    rm glew-$GLEW_VER.tgz && \
    cd glew-$GLEW_VER && cd auto && \
    make && \
    cd .. && \
    make SYSTEM=linux-osmesa && make install && make clean && \
    rm -rf /glew-$GLEW_VER

ENV LD_LIBRARY_PATH=/usr/lib64:$LD_LIBRARY_PATH

CMD ["/bin/bash", "-l"]
