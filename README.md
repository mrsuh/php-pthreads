# PHP PThreads

Library adds threading functionality using the [pthreads](https://ru.wikipedia.org/wiki/POSIX_Threads) library and PHP FFI

:warning: WIP

### Requirements
* PHP >= 7.4 (with FFI and ZTS)
* Linux(x86_64) / Darwin(x86_64)

## Usage

```php
<?php

require_once __DIR__ . '/../vendor/autoload.php';

use \Mrsuh\PhpThread;

PhpThread::run(function() {
    sleep(5);
    echo "hello1\n";
});

PhpThread::run(function() {
    sleep(5);
    echo "hello2\n";
});

PhpThread::wait();
```

## For contributors

### How to compile library
```bash
git clone --recurse-submodules git@github.com:mrsuh/php-pthreads.git && cd php-pthreads
cd php-src
./buildconf --force
./configure --disable-all --with-ffi --enable-zts --with-iconv=$(brew --prefix libiconv)
cd ..
make DEBUG=1
```
