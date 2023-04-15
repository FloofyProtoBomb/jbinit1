#include <jbinit.h>

void pinfo_check(bool* use_fakefs_p, char* bootargs, char* dev_rootdev) {
  struct stat statbuf;
  if (checkrain_option_enabled(pinfo.flags, palerain_option_rootful) &&
      (checkrain_option_enabled(pinfo.flags, palerain_option_force_fakefs) ||
      !checkrain_option_enabled(pinfo.flags, palerain_option_no_ssv))) {
    snprintf(dev_rootdev, 0x20, "/dev/%s", pinfo.rootdev);
    *use_fakefs_p = true;
  }

  if (checkrain_option_enabled(info.flags, checkrain_option_force_revert)) {
    *use_fakefs_p = false;
  }

  if (checkrain_option_enabled(pinfo.flags, palerain_option_setup_rootful)) {
    *use_fakefs_p = false;
    if (!checkrain_option_enabled(pinfo.flags, palerain_option_rootful)) {
      LOG("cannot setup fakefs without being in rootful mode is unset\n");
      spin();
    }
    if (!checkrain_option_enabled(pinfo.flags, palerain_option_force_fakefs) 
      && checkrain_option_enabled(pinfo.flags, palerain_option_no_ssv)) {
      LOG("fakefs not allowed without SSV");
      spin();
    }

    if (strstr(bootargs, "wdt=-1") == NULL) {
      LOG("cannot have palerain_option_setup_rootful without wdt=-1 in boot-args\n");
      spin();
    }
    if (stat(dev_rootdev, &statbuf) == 0) {
      if (!checkrain_option_enabled(pinfo.flags, palerain_option_setup_rootful_forced) &&
      !checkrain_option_enabled(info.flags, checkrain_option_force_revert) ) {
        LOG("cannot create fakefs over an existing one without --force-revert\n");
        spin();
      }
    }
    if (checkrain_option_enabled(pinfo.flags, palerain_option_setup_rootful_forced)) {
      puts("Warning: this flag is deprecated, use --force-revert with -c/-B to recreate fakefs/partial fakefs");
    }
  } else if (checkrain_option_enabled(pinfo.flags, palerain_option_setup_partial_root)) {
    LOG("cannot have palerain_option_setup_partial_root without palerain_option_setup_rootful\n");
    spin();
  }
}
