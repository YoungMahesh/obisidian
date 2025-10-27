
### hardhat compile
#### build info file doesn't exist during execution of `hardhat ignition`
```bash
npx hardhat ignition deploy ignition/modules/Counter.ts --network sepoliaArbitrum --verify
<project-path>/cache/build-info/solc-0_8_28-9f3807964c0a855bc2b5a77e8122427e3ff3fb40.output.json not found
```

- solution
	- pass `--build-profile`  argument to the command
	- e.g. `npx hardhat ignition deploy ignition/modules/Counter.ts --build-profile default --network sepoliaArbitrum --verify`

## hardhat network

### errors

- Nonce too high. Expected nonce to be 0 but got 3. Note that transactions can't be queued when automining.
  - if happened during metamask transaction, then Metamsk -> settings -> advanced -> Click 'Clear activity tab data'
