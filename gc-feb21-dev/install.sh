#!/bin/bash
if [ $UID -ne 0 ]; then
    echo "run as root"
    exit -1
fi
. /u01/app/oracle/product/11.2.0/xe/bin/oracle_env.sh
sqlplus system/manager @scripts/db_oracle.sql
mkdir /opt/gcApp
cp -R bin /opt/gcApp/
