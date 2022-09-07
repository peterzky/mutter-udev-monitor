# mutter-udev-monitor
select mutter primary gpu based on monitor connection

udev rules
```
 SUBSYSTEM=="drm", DRIVERS=="nvidia", PROGRAM="${pkgs.gnome-gpu-selector}/bin/gpu nvidia", RESULT=="connected", TAG+="mutter-device-preferred-primary"
```
