# Run in docker

Simple and fast setup of IWILL.IO on Docker is also available.

## Install Dependencies

- [Docker](https://docs.docker.com) Docker 17.05 or higher is required
- [docker-compose](https://docs.docker.com/compose/) version >= 1.10.0

## Docker Requirement

- At least 7GB RAM (Docker -> Preferences -> Advanced -> Memory -> 7GB or above)
- If the build below fails, make sure you've adjusted Docker Memory settings and try again.

## Build iwill image

```bash
git clone https://github.com/IWILLIO/iwill.git --recursive  --depth 1
cd iwill/Docker
docker build . -t iwillio/iwill
```

The above will build off the most recent commit to the master branch by default. If you would like to target a specific branch/tag, you may use a build argument. For example, if you wished to generate a docker image based off of the v1.4.1 tag, you could do the following:

```bash
docker build -t iwillio/iwill:v1.4.1 --build-arg branch=v1.4.1 .
```

By default, the symbol in iwillio.system is set to SYS. You can override this using the symbol argument while building the docker image.

```bash
docker build -t iwillio/iwill --build-arg symbol=<symbol> .
```

## Start nodiwill docker container only

```bash
docker run --name nodiwill -p 8888:8888 -p 9876:9876 -t iwillio/iwill nodiwilld.sh -e --http-alias=nodiwill:8888 --http-alias=127.0.0.1:8888 --http-alias=localhost:8888 arg1 arg2
```

By default, all data is persisted in a docker volume. It can be deleted if the data is outdated or corrupted:

```bash
$ docker inspect --format '{{ range .Mounts }}{{ .Name }} {{ end }}' nodiwill
fdc265730a4f697346fa8b078c176e315b959e79365fc9cbd11f090ea0cb5cbc
$ docker volume rm fdc265730a4f697346fa8b078c176e315b959e79365fc9cbd11f090ea0cb5cbc
```

Alternately, you can directly mount host directory into the container

```bash
docker run --name nodiwill -v /path-to-data-dir:/opt/iwillio/bin/data-dir -p 8888:8888 -p 9876:9876 -t iwillio/iwill nodiwilld.sh -e --http-alias=nodiwill:8888 --http-alias=127.0.0.1:8888 --http-alias=localhost:8888 arg1 arg2
```

## Get chain info

```bash
curl http://127.0.0.1:8888/v1/chain/get_info
```

## Start both nodiwill and kiwilld containers

```bash
docker volume create --name=nodiwill-data-volume
docker volume create --name=kiwilld-data-volume
docker-compose up -d
```

After `docker-compose up -d`, two services named `nodiwilld` and `kiwilld` will be started. nodiwill service would expose ports 8888 and 9876 to the host. kiwilld service does not expose any port to the host, it is only accessible to cliwill when running cliwill is running inside the kiwilld container as described in "Execute cliwill commands" section.

### Execute cliwill commands

You can run the `cliwill` commands via a bash alias.

```bash
alias cliwill='docker-compose exec kiwilld /opt/iwillio/bin/cliwill -u http://nodiwilld:8888 --wallet-url http://localhost:8900'
cliwill get info
cliwill get account inita
```

Upload sample exchange contract

```bash
cliwill set contract exchange contracts/exchange/
```

If you don't need kiwilld afterwards, you can stop the kiwilld service using

```bash
docker-compose stop kiwilld
```

### Develop/Build custom contracts

Due to the fact that the iwillio/iwill image does not contain the required dependencies for contract development (this is by design, to keep the image size small), you will need to utilize the iwillio/iwill-dev image. This image contains both the required binaries and dependencies to build contracts using iwilliocpp.

You can either use the image available on [Docker Hub](https://hub.docker.com/r/iwillio/iwill-dev/) or navigate into the dev folder and build the image manually.

```bash
cd dev
docker build -t iwillio/iwill-dev .
```

### Change default configuration

You can use docker compose override file to change the default configurations. For example, create an alternate config file `config2.ini` and a `docker-compose.override.yml` with the following content.

```yaml
version: "2"

services:
  nodiwill:
    volumes:
      - nodiwill-data-volume:/opt/iwillio/bin/data-dir
      - ./config2.ini:/opt/iwillio/bin/data-dir/config.ini
```

Then restart your docker containers as follows:

```bash
docker-compose down
docker-compose up
```

### Clear data-dir

The data volume created by docker-compose can be deleted as follows:

```bash
docker volume rm nodiwill-data-volume
docker volume rm kiwilld-data-volume
```

### Docker Hub

Docker Hub image available from [docker hub](https://hub.docker.com/r/iwillio/iwill/).
Create a new `docker-compose.yaml` file with the content below

```bash
version: "3"

services:
  nodiwilld:
    image: iwillio/iwill:latest
    command: /opt/iwillio/bin/nodiwilld.sh --data-dir /opt/iwillio/bin/data-dir -e --http-alias=nodiwilld:8888 --http-alias=127.0.0.1:8888 --http-alias=localhost:8888
    hostname: nodiwilld
    ports:
      - 8888:8888
      - 9876:9876
    expose:
      - "8888"
    volumes:
      - nodiwill-data-volume:/opt/iwillio/bin/data-dir

  kiwilld:
    image: iwillio/iwill:latest
    command: /opt/iwillio/bin/kiwilld --wallet-dir /opt/iwillio/bin/data-dir --http-server-address=127.0.0.1:8900 --http-alias=localhost:8900 --http-alias=kiwilld:8900
    hostname: kiwilld
    links:
      - nodiwilld
    volumes:
      - kiwilld-data-volume:/opt/iwillio/bin/data-dir

volumes:
  nodiwill-data-volume:
  kiwilld-data-volume:

```

*NOTE:* the default version is the latest, you can change it to what you want

run `docker pull iwillio/iwill:latest`

run `docker-compose up`

### IWILLIO Testnet

We can easily set up a IWILLIO local testnet using docker images. Just run the following commands:

Note: if you want to use the mongo db plugin, you have to enable it in your `data-dir/config.ini` first.

```
# create volume
docker volume create --name=nodiwill-data-volume
docker volume create --name=kiwilld-data-volume
# pull images and start containers
docker-compose -f docker-compose-iwillio-latest.yaml up -d
# get chain info
curl http://127.0.0.1:8888/v1/chain/get_info
# get logs
docker-compose logs -f nodiwilld
# stop containers
docker-compose -f docker-compose-iwillio-latest.yaml down
```

The `blocks` data are stored under `--data-dir` by default, and the wallet files are stored under `--wallet-dir` by default, of course you can change these as you want.

### About MongoDB Plugin

Currently, the mongodb plugin is disabled in `config.ini` by default, you have to change it manually in `config.ini` or you can mount a `config.ini` file to `/opt/iwillio/bin/data-dir/config.ini` in the docker-compose file.
