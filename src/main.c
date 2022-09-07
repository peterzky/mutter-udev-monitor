#include <libudev.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Usage: gpu [driver name]\n e.g gpu nvidia.");
    exit(EXIT_FAILURE);
  }

  struct udev *udev;
  struct udev_enumerate *enumerate_pci, *enumerate_drm;
  struct udev_list_entry *devices, *dev_list_entry;
  struct udev_device *dev;
  int monitor_counter = 0;

  /* Create the udev object */
  udev = udev_new();
  if (!udev) {
    printf("Can't create udev\n");
    exit(1);
  }

  /* Find nvidia graphcis */
  enumerate_pci = udev_enumerate_new(udev);
  udev_enumerate_add_match_subsystem(enumerate_pci, "pci");
  udev_enumerate_add_match_sysattr(enumerate_pci, "driver", argv[1]);
  udev_enumerate_scan_devices(enumerate_pci);
  devices = udev_enumerate_get_list_entry(enumerate_pci);

  /* Create drm enumerate */
  enumerate_drm = udev_enumerate_new(udev);

  udev_list_entry_foreach(dev_list_entry, devices) {
    const char *path;
    path = udev_list_entry_get_name(dev_list_entry);
    dev = udev_device_new_from_syspath(udev, path);
    udev_enumerate_add_match_parent(enumerate_drm, dev);
    /* printf("%s\n", udev_device_get_syspath(dev)); */
    udev_device_unref(dev);
  }

  /* Filter drm monitor connection status */
  udev_enumerate_add_match_subsystem(enumerate_drm, "drm");
  udev_enumerate_add_match_sysattr(enumerate_drm, "status", "connected");
  udev_enumerate_scan_devices(enumerate_drm);

  devices = udev_enumerate_get_list_entry(enumerate_drm);

  udev_list_entry_foreach(dev_list_entry, devices) {
    /* const char *path; */
    /* path = udev_list_entry_get_name(dev_list_entry); */
    /* dev = udev_device_new_from_syspath(udev, path); */
    /* printf("%s\n", path); */
    /* udev_device_unref(dev); */
    monitor_counter++;
  };

  /* Free the enumerator object */
  udev_enumerate_unref(enumerate_pci);
  udev_enumerate_unref(enumerate_drm);
  udev_unref(udev);

  if (monitor_counter > 0) {
    fprintf(stdout, "connected");
  } else {
    fprintf(stdout, "disconnected");
  }

  return EXIT_SUCCESS;
}
