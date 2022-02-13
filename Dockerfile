FROM debian:buster-slim

RUN set -eux; \
	apt-get update; \
	apt-get install -y --no-install-recommends \
		autoconf \
		dpkg-dev \
		file \
		g++ \
		gcc \
		libc-dev \
		make \
		pkg-config \
		re2c \
		build-essential \
		bison \
		libxml2-dev \
		libffi-dev \
		libsqlite3-dev;

COPY . /code

WORKDIR /code/php-src

RUN ./buildconf --force
RUN ./configure --disable-all --with-ffi --enable-zts

RUN make -j "$(nproc)"
RUN make install

WORKDIR /code
