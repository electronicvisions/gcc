#!/bin/bash -x
set -o errexit

cd gcc
export ftp_proxy=$http_proxy
contrib/download_prerequisites
cd ..
