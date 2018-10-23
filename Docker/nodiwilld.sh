#!/bin/sh
cd /opt/iwillio/bin

if [ ! -d "/opt/iwillio/bin/data-dir" ]; then
    mkdir /opt/iwillio/bin/data-dir
fi

if [ -f '/opt/iwillio/bin/data-dir/config.ini' ]; then
    echo
  else
    cp /config.ini /opt/iwillio/bin/data-dir
fi

if [ -d '/opt/iwillio/bin/data-dir/contracts' ]; then
    echo
  else
    cp -r /contracts /opt/iwillio/bin/data-dir
fi

while :; do
    case $1 in
        --config-dir=?*)
            CONFIG_DIR=${1#*=}
            ;;
        *)
            break
    esac
    shift
done

if [ ! "$CONFIG_DIR" ]; then
    CONFIG_DIR="--config-dir=/opt/iwillio/bin/data-dir"
else
    CONFIG_DIR=""
fi

exec /opt/iwillio/bin/nodiwill $CONFIG_DIR "$@"
