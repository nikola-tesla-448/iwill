#! /bin/bash

binaries=(cliwill
          iwillio-abigen
          iwillio-launcher
          iwillio-s2wasm
          iwillio-wast2wasm
          iwilliocpp
          kiwilld
          nodiwill
          iwillio-applesdemo)

if [ -d "/usr/local/iwillio" ]; then
   printf "\tDo you wish to remove this install? (requires sudo)\n"
   select yn in "Yes" "No"; do
      case $yn in
         [Yy]* )
            if [ "$(id -u)" -ne 0 ]; then
               printf "\n\tThis requires sudo, please run ./iwillio_uninstall.sh with sudo\n\n"
               exit -1
            fi

            pushd /usr/local &> /dev/null
            rm -rf iwillio
            pushd bin &> /dev/null
            for binary in ${binaries[@]}; do
               rm ${binary}
            done
            # Handle cleanup of directories created from installation
            if [ "$1" == "--full" ]; then
               if [ -d ~/Library/Application\ Support/iwillio ]; then rm -rf ~/Library/Application\ Support/iwillio; fi # Mac OS
               if [ -d ~/.local/share/iwillio ]; then rm -rf ~/.local/share/iwillio; fi # Linux
            fi
            popd &> /dev/null
            break;;
         [Nn]* )
            printf "\tAborting uninstall\n\n"
            exit -1;;
      esac
   done
fi
