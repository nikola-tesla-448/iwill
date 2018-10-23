The following steps must be taken for the example script to work.

0. Create wallet
0. Create account for iwillio.token
0. Create account for scott
0. Create account for exchange
0. Set token contract on iwillio.token
0. Create IWILL token
0. Issue initial tokens to scott

**Note**:
Deleting the `transactions.txt` file will prevent replay from working.


### Create wallet
`cliwill wallet create`

### Create account steps
`cliwill create key`

`cliwill create key`

`cliwill wallet import  --private-key <private key from step 1>`

`cliwill wallet import  --private-key <private key from step 2>`

`cliwill create account iwillio <account_name> <public key from step 1> <public key from step 2>`

### Set contract steps
`cliwill set contract iwillio.token /contracts/iwillio.token -p iwillio.token@active`

### Create IWILL token steps
`cliwill push action iwillio.token create '{"issuer": "iwillio.token", "maximum_supply": "100000.0000 IWILL", "can_freeze": 1, "can_recall": 1, "can_whitelist": 1}' -p iwillio.token@active`

### Issue token steps
`cliwill push action iwillio.token issue '{"to": "scott", "quantity": "900.0000 IWILL", "memo": "testing"}' -p iwillio.token@active`
