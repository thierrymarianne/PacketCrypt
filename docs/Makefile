SHELL:=/bin/bash

.PHONY: help

check_requirements=/bin/bash -c '( ( test -z "'$$MINING_POOL'" || test -z "'$$WALLET_ADDRESS'" ) && \
echo "Your wallet address and mining pool are to be declared as environment variables e.g." && \
echo "export WALLET_ADDRESS='"'"'__FILL_ME__'"'"' MINING_POOL='"'"'__FILL_ME__'"'"'" && false ) || \
( test -n "'$$MINING_POOL'" && test -n "'$$WALLET_ADDRESS'" && \
echo "About to mine via \"'$$MINING_POOL'\" on behalf of \"'$$WALLET_ADDRESS'\"" )'

cmd=/usr/local/bin/node blkmine --paymentAddr=$$WALLET_ADDRESS $$MINING_POOL

run_with_docker=docker run -e WALLET_ADDRESS=$$WALLET_ADDRESS -e MINING_POOL=$$MINING_POOL \
	--network host -d --name blkpacketcrypt blkpacketcrypt

list_running_packetcrypt_containers=docker ps -a --format '{{ .ID  }}\t{{.Image}}' | \grep blkpacketcryp[t] | \awk -v FS='\t' -v OFS='\t' '{print $$1}'

help:
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

build: ## Build container
	@/bin/bash -c "docker build -t blkpacketcrypt .."

start-mining: ## Run container requiring having exported a wallet address and a mining pool as environment variables i.e. export WALLET_ADDRESS='__FILL_ME__ MINING_POOL='__FILL_ME__'
	@$(check_requirements) && /bin/bash -c "${run_with_docker} ${cmd}"

stop-mining: ## Stop existing mining container
	@$(list_running_packetcrypt_containers) | xargs -I{} docker rm -f {}

tail-logs: ## Tail running container logs
	@$(list_running_packetcrypt_containers) | xargs -I{} docker logs -f {}
