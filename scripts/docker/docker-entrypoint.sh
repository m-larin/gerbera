#!/usr/bin/env sh

if [ ! -d /var/run/gerbera/.config/gerbera ]; then
  # Make default config dir (only applies of config was generated by older version)
  mkdir -p /var/run/gerbera/.config/gerbera
fi

if [ ! -f /var/run/gerbera/config.xml ]; then
  # Generate a config file with home set
  gerbera --create-config --home /var/run/gerbera > /var/run/gerbera/config.xml

  # Automatically scan /content with inotify (for a volume mount)
  sed 's/<import hidden-files="no">/<import hidden-files="no">\n\
    <autoscan use-inotify="yes">\n\
    <directory location="\/content" mode="inotify" \
    recursive="yes" hidden-files="no"\/>\n\
    <\/autoscan>/' -i /var/run/gerbera/config.xml
fi

if [ -e /dev/video10 ]; then
  # Add permission to all users on /dev/video10 device
  chown root:video /dev/video10
fi

if [ -e /dev/video11 ]; then
  # Add permission to all users on /dev/video11 device
  chown root:video /dev/video11
fi

if [ -e /dev/video12 ]; then
  # Add permission to all users on /dev/video12 device
  chown root:video /dev/video12
fi

if [ -e /dev/dri ]; then
  # Add permission to all users on /dev/dri device
  chown root:video /dev/dri
fi

# If we are root, chown home and drop privs
if [ "$1" = 'gerbera' -a "$(id -u)" = '0' ]; then
    chown -R gerbera /var/run/gerbera
    exec su-exec gerbera "$@"
else
    # Otherwise run as the user provided
    exec "$@"
fi
