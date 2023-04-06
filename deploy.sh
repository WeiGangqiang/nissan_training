#!/bin/bash
set +e

GTEST_DIR=/code/Turing/nissan_training/output/gtest/lib

function main() {
  local user=$1
  local password=$2
  local remote_host=$3
  sshpass -p "${password}" ssh "${user}@${remote_host}" "mkdir -p ${GTEST_DIR}"
  sshpass -p "${password}" scp ./output/gtest/lib/libgtest.so ${user}@${remote_host}:/${GTEST_DIR}
  sshpass -p "${password}" scp ./output/gtest/lib/libgtest_main.so ${user}@${remote_host}:/${GTEST_DIR}
  sshpass -p "${password}" scp ./build/test/fota_test.so ${user}@${remote_host}:/usr/bin/
}

main "$@"
set -e
