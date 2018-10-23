FROM iwillio/builder
ARG branch=master
ARG symbol=SYS

RUN git clone -b $branch https://github.com/IWILLIO/iwill.git --recursive \
    && cd iwill && echo "$branch:$(git rev-parse HEAD)" > /etc/iwillio-version \
    && cmake -H. -B"/opt/iwillio" -GNinja -DCMAKE_BUILD_TYPE=Release -DWASM_ROOT=/opt/wasm -DCMAKE_CXX_COMPILER=clang++ \
       -DCMAKE_C_COMPILER=clang -DCMAKE_INSTALL_PREFIX=/opt/iwillio -DBUILD_MONGO_DB_PLUGIN=true -DCORE_SYMBOL_NAME=$symbol \
    && cmake --build /opt/iwillio --target install \
    && cp /iwill/Docker/config.ini / && ln -s /opt/iwillio/contracts /contracts && cp /iwill/Docker/nodiwilld.sh /opt/iwillio/bin/nodiwilld.sh && ln -s /iwill/tutorials /tutorials

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get -y install openssl ca-certificates vim psmisc python3-pip && rm -rf /var/lib/apt/lists/*
RUN pip3 install numpy
ENV IWILLIO_ROOT=/opt/iwillio
RUN chmod +x /opt/iwillio/bin/nodiwilld.sh
ENV LD_LIBRARY_PATH /usr/local/lib
ENV PATH /opt/iwillio/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
