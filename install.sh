main() {
  # Use colors, but only if connected to a terminal, and that terminal
  # supports them.
  if which tput >/dev/null 2>&1; then
      ncolors=$(tput colors)
  fi
  if [ -t 1 ] && [ -n "$ncolors" ] && [ "$ncolors" -ge 8 ]; then
    RED="$(tput setaf 1)"
    GREEN="$(tput setaf 2)"
    YELLOW="$(tput setaf 3)"
    BLUE="$(tput setaf 4)"
    BOLD="$(tput bold)"
    NORMAL="$(tput sgr0)"
  else
    RED=""
    GREEN=""
    YELLOW=""
    BLUE=""
    BOLD=""
    NORMAL=""
  fi

  printf "${BLUE}Cloning cctest...${NORMAL}\n"

  hash git >/dev/null 2>&1 || {
    echo "Error: git is not installed"
    exit 1
  }

  env git clone https://github.com/ccup/cctest.git || {
    printf "Error: git clone of cctest repo failed\n"
    exit 1
  }

  printf "${BLUE}Looking for an existing cctest...${NORMAL}\n"
  if [ -f /usr/local/lib/libcctest.a ]; then
    printf "${YELLOW}Found cctest installed.${NORMAL} ${GREEN}Clearing prev version.${NORMAL}\n";
    sudo rm -rf /usr/local/include/cctest
    sudo rm -rf /usr/local/lib/cmake/cctest    
    sudo rm -rf /usr/local/lib/libcctest.a
    sudo rm -rf /usr/local/lib/libcctest_main.a    
  fi

  cd cctest
  mkdir build && cd build
  cmake -DCCTEST_RUN_TESTS=off ..

  printf "${BLUE}make cctest...${NORMAL}\n"
  env make || {
    printf "Error: install cctest failed.\n"
    exit 1
  }

  sudo make install

  printf "${GREEN}"
  echo ''
  echo 'cctest is now installed!'
  echo ''
  echo 'p.s. Follow us at https://github.com/ccup/cctest'
  echo ''
  printf "${NORMAL}"
}

main