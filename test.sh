#!/bin/bash

./test/bin/crud || { exit 1; }

./test/bin/list || { exit 1; }

./test/bin/test || { exit 1; }
