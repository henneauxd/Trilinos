# This script is sourced to return all of the supported builds

export ATDM_CONFIG_CTEST_S_BUILD_NAME_PREFIX=Trilinos-atdm-

export ATDM_CONFIG_ALL_SUPPORTED_BUILDS=(
  cee-rhel6_clang-5.0.1_openmpi-4.0.1_serial_static_opt    # SPARC CI build
  cee-rhel6_gnu-7.2.0_openmpi-4.0.1_serial_shared_opt      # SPARC CI build
  cee-rhel6_intel-18.0.2_mpich2-3.2_openmp_static_opt      # SPARC CI build
  cee-rhel6_intel-19.0.3_intelmpi-2018.4_serial_static_opt # SPARC Nightly bulid
  )
