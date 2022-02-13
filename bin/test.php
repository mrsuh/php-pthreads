<?php

require_once __DIR__ . '/../vendor/autoload.php';

use \Mrsuh\PhpThread;

PhpThread::run(function() {
    echo "hello\n";
});

PhpThread::wait();
