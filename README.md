[![Build Status](https://travis-ci.org/Goganych/lab10.svg?branch=master)](https://travis-ci.org/Goganych/lab10)
the demo application redirects data from stdin to a file **log.txt** using a package **print**.
Laboratory work X

Данная лабораторная работа посвещена изучению систем управления пакетами на примере Hunter

$ open https://github.com/ruslo/hunter
Tasks

 1. Создать публичный репозиторий с названием lab10 на сервисе GitHub
 2. Сгенирировать токен для доступа к сервису GitHub с правами repo
 3. Выполнить инструкцию учебного материала
 4. Ознакомиться со ссылками учебного материала
 5. Составить отчет и отправить ссылку личным сообщением в Slack
Tutorial

$ export GITHUB_USERNAME=<имя_пользователя>
$ export GITHUB_TOKEN=<сгенирированный_токен>
$ cd ${GITHUB_USERNAME}/workspace
$ pushd .
$ source scripts/activate
$ go get github.com/github/hub
$ mkdir ~/.config
$ cat > ~/.config/hub <<EOF
github.com:
- user: ${GITHUB_USERNAME}
  oauth_token: ${GITHUB_TOKEN}
  protocol: https
EOF
$ git config --global hub.protocol https
$ wget https://github.com/${GITHUB_USERNAME}/lab09/archive/v0.1.0.0.tar.gz
$ export PRINT_SHA1=`openssl sha1 v0.1.0.0.tar.gz | cut -d'=' -f2 | cut -c2-41`
$ echo $PRINT_SHA1
$ rm -rf v0.1.0.0.tar.gz
$ git clone https://github.com/ruslo/hunter projects/hunter
$ cd projects/hunter && git checkout v0.19.137
$ git remote show
$ hub fork
$ git remote show
$ git remote show ${GITHUB_USERNAME}
$ mkdir cmake/projects/print
$ cat > cmake/projects/print/hunter.cmake <<EOF
include(hunter_add_version)
include(hunter_cacheable)
include(hunter_cmake_args)
include(hunter_download)
include(hunter_pick_scheme)

hunter_add_version(
    PACKAGE_NAME
    print
    VERSION
    "0.1.0.0"
    URL
    "https://github.com/${GITHUB_USERNAME}/lab09/archive/v0.1.0.0.tar.gz"
    SHA1
    ${PRINT_SHA1}
)

hunter_pick_scheme(DEFAULT url_sha1_cmake)

hunter_cmake_args(
    print
    CMAKE_ARGS
    BUILD_EXAMPLES=NO
    BUILD_TESTS=NO
)
hunter_cacheable(print)
hunter_download(PACKAGE_NAME print)
EOF
$ cat >> cmake/configs/default.cmake <<EOF
hunter_config(print VERSION 0.1.0.0)
EOF
$ git add .
$ git commit -m"added print package"
$ git push ${GIHUB_USERNAME} master
$ git tag v0.19.137.1
$ git push ${GIHUB_USERNAME} master --tags
$ cd ..
$ export HUNTER_ROOT=`pwd`/hunter
$ mkdir lab10 && cd lab10
$ git init
$ git remote add origin https://github.com/${GITHUB_USERNAME}/lab10
$ mkdir sources
$ cat > sources/demo.cpp <<EOF
#include <print.hpp>

int main(int argc, char** argv) {
	std::string text;
	while(std::cin >> text) {
		std::ofstream out("log.txt", std::ios_base::app);
		print(text, out);
		out << std::endl;
	}
}
EOF
$ wget https://github.com/hunter-packages/gate/archive/v0.8.1.tar.gz 
$ tar -xzvf v0.8.1.tar.gz gate-0.8.1/cmake/HunterGate.cmake
$ mkdir cmake
$ mv gate-0.8.1/cmake/HunterGate.cmake cmake
$ rm -rf gate*/
$ rm *.tar.gz
$ cat > CMakeLists.txt <<EOF
cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)
EOF
$ wget https://github.com/${GITHUB_USERNAME}/hunter/archive/v0.19.137.1.tar.gz
$ export HUNTER_SHA1=`openssl sha1 v0.19.137.1.tar.gz | cut -d'=' -f2 | cut -c2-41`
$ echo $HUNTER_SHA1
$ rm -rf v0.19.137.1.tar.gz
$ cat >> CMakeLists.txt <<EOF

include(cmake/HunterGate.cmake)

HunterGate(
    URL "https://github.com/${GITHUB_USERNAME}/hunter/archive/v0.19.137.1.tar.gz"
    SHA1 "${HUNTER_SHA1}"
)
EOF
$ cat >> CMakeLists.txt <<EOF

project(demo)

hunter_add_package(print)
find_package(print)

add_executable(demo \${CMAKE_CURRENT_SOURCE_DIR}/sources/demo.cpp)
target_link_libraries(demo print)

install(TARGETS demo RUNTIME DESTINATION bin)
EOF
$ cat > .gitignore <<EOF
*build*/
*install*/
*.swp
EOF
$ cat > README.md <<EOF
[![Build Status](https://travis-ci.org/${GITHUB_USERNAME}/lab10.svg?branch=master)](https://travis-ci.org/${GITHUB_USERNAME}/lab10)
the demo application redirects data from stdin to a file **log.txt** using a package **print**.
EOF
$ cat > .travis.yml <<EOF
language: cpp

script:   
- cmake -H. -B_build
- cmake --build _build
EOF
$ travis lint
$ git add .
$ git commit -m"first commit"
$ git push origin master
$ travis login --auto
$ travis enable
$ cmake -H. -B_build -DCMAKE_INSTALL_PREFIX=_install
$ cmake --build _build --target install
$ mkdir artifacts && cd artifacts
$ echo "text1 text2 text3" | ../_install/bin/demo
$ cat log.txt
Report

$ popd
$ export LAB_NUMBER=10
$ git clone https://github.com/tp-labs/lab${LAB_NUMBER} tasks/lab${LAB_NUMBER}
$ mkdir reports/lab${LAB_NUMBER}
$ cp tasks/lab${LAB_NUMBER}/README.md reports/lab${LAB_NUMBER}/REPORT.md
$ cd reports/lab${LAB_NUMBER}
$ edit REPORT.md
$ gistup -m "lab${LAB_NUMBER}"
Links

hub
polly
conan
Copyright (c) 2017 Братья Вершинины
