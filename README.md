# cmake_vcpkg_solidity

This is a simple example that shows how you can add the solidity compiler libraries into your C++ project using `cmake`and `vcpkg`.

To get used to the internal API's just take a look into our [test-cases](https://github.com/ethereum/solidity/tree/develop/test). A good starting point are probably our [`StandardCompiler`tests](https://github.com/ethereum/solidity/blob/develop/test/libsolidity/StandardCompiler.cpp). 
Our [documentation](https://docs.soliditylang.org/en/latest/) might be also helpful.

## Clone, Compile & Run Example

```bash
# Clone
$ git clone git@github.com:aarlt/cmake_vcpkg_solidity.git --recursive

$ cd cmake_vcpkg_solidity
$ mkdir build
$ cd build

# Compile
$ cmake ..
$ make -j

# Run
$ ./cmake_vcpkg_solidity
```

## Input

### Contract
```solidity
// SPDX-License-Identifier: GPL-3.0
pragma solidity >=0.7.0 <0.9.0;
contract C {
    function d() public {
    }
    function e() public payable returns (uint) {
        return msg.value;
    }
}
```

### Standard JSON

The compiler uses a special JSON format (called `Standard JSON`) to retrieve the contract sources and compiler otions. This format is defined in our [documentation]( https://docs.soliditylang.org/en/latest/using-the-compiler.html#compiler-input-and-output-json-description).

```json
{
  "language": "Solidity",
  "sources": {
    "contract.sol": {
      "content": "<..>"
    }
  },
  "settings": {
    "outputSelection": {
      "contract.sol": {
        "C": [
          "abi",
          "devdoc",
          "userdoc",
          "evm.bytecode",
          "evm.assembly",
          "evm.gasEstimates",
          "metadata"
        ],
        "": [
          "ast"
        ]
      }
    }
  }
}
```

## Output

```json
{
  "contracts": {
    "contract.sol": {
      "C": {
        "abi": [
          {
            "inputs": [],
            "name": "d",
            "outputs": [],
            "stateMutability": "nonpayable",
            "type": "function"
          },
          {
            "inputs": [],
            "name": "e",
            "outputs": [
              {
                "internalType": "uint256",
                "name": "",
                "type": "uint256"
              }
            ],
            "stateMutability": "payable",
            "type": "function"
          }
        ],
        "devdoc": {
          "kind": "dev",
          "methods": {},
          "version": 1
        },
        "evm": {
          "assembly": "    /* \"contract.sol\":68:195  contract C {... */\n  mstore(0x40, 0x80)\n  callvalue\n  dup1\n  iszero\n  tag_1\n  jumpi\n  0x00\n  dup1\n  revert\ntag_1:\n  pop\n  dataSize(sub_0)\n  dup1\n  dataOffset(sub_0)\n  0x00\n  codecopy\n  0x00\n  return\nstop\n\nsub_0: assembly {\n        /* \"contract.sol\":68:195  contract C {... */\n      mstore(0x40, 0x80)\n      jumpi(tag_1, lt(calldatasize, 0x04))\n      shr(0xe0, calldataload(0x00))\n      dup1\n      0x8a054ac2\n      eq\n      tag_2\n      jumpi\n      dup1\n      0xffae15ba\n      eq\n      tag_3\n      jumpi\n    tag_1:\n      0x00\n      dup1\n      revert\n        /* \"contract.sol\":85:112  function d() public {... */\n    tag_2:\n      callvalue\n      dup1\n      iszero\n      tag_4\n      jumpi\n      0x00\n      dup1\n      revert\n    tag_4:\n      pop\n      tag_5\n      tag_6\n      jump // in\n    tag_5:\n      stop\n        /* \"contract.sol\":117:193  function e() public payable returns (uint) {... */\n    tag_3:\n      tag_7\n      tag_8\n      jump // in\n    tag_7:\n      mload(0x40)\n      tag_9\n      swap2\n      swap1\n      tag_10\n      jump // in\n    tag_9:\n      mload(0x40)\n      dup1\n      swap2\n      sub\n      swap1\n      return\n        /* \"contract.sol\":85:112  function d() public {... */\n    tag_6:\n      jump // out\n        /* \"contract.sol\":117:193  function e() public payable returns (uint) {... */\n    tag_8:\n        /* \"contract.sol\":154:158  uint */\n      0x00\n        /* \"contract.sol\":177:186  msg.value */\n      callvalue\n        /* \"contract.sol\":170:186  return msg.value */\n      swap1\n      pop\n        /* \"contract.sol\":117:193  function e() public payable returns (uint) {... */\n      swap1\n      jump // out\n        /* \"#utility.yul\":7:84   */\n    tag_13:\n        /* \"#utility.yul\":44:51   */\n      0x00\n        /* \"#utility.yul\":73:78   */\n      dup2\n        /* \"#utility.yul\":62:78   */\n      swap1\n      pop\n        /* \"#utility.yul\":7:84   */\n      swap2\n      swap1\n      pop\n      jump // out\n        /* \"#utility.yul\":90:208   */\n    tag_14:\n        /* \"#utility.yul\":177:201   */\n      tag_18\n        /* \"#utility.yul\":195:200   */\n      dup2\n        /* \"#utility.yul\":177:201   */\n      tag_13\n      jump // in\n    tag_18:\n        /* \"#utility.yul\":172:175   */\n      dup3\n        /* \"#utility.yul\":165:202   */\n      mstore\n        /* \"#utility.yul\":90:208   */\n      pop\n      pop\n      jump // out\n        /* \"#utility.yul\":214:436   */\n    tag_10:\n        /* \"#utility.yul\":307:311   */\n      0x00\n        /* \"#utility.yul\":345:347   */\n      0x20\n        /* \"#utility.yul\":334:343   */\n      dup3\n        /* \"#utility.yul\":330:348   */\n      add\n        /* \"#utility.yul\":322:348   */\n      swap1\n      pop\n        /* \"#utility.yul\":358:429   */\n      tag_20\n        /* \"#utility.yul\":426:427   */\n      0x00\n        /* \"#utility.yul\":415:424   */\n      dup4\n        /* \"#utility.yul\":411:428   */\n      add\n        /* \"#utility.yul\":402:408   */\n      dup5\n        /* \"#utility.yul\":358:429   */\n      tag_14\n      jump // in\n    tag_20:\n        /* \"#utility.yul\":214:436   */\n      swap3\n      swap2\n      pop\n      pop\n      jump // out\n\n    auxdata: 0xa2646970667358221220b890ede9d2428faac28aa986d319e37a797e3b8f4daee4504a5960fc2d16025d64736f6c637828302e382e32352d646576656c6f702e323032342e322e31372b636f6d6d69742e65356165643266330059\n}\n",
          "bytecode": {
            "functionDebugData": {},
            "generatedSources": [],
            "linkReferences": {},
            "object": "608060405234801561000f575f80fd5b5060e88061001c5f395ff3fe6080604052600436106025575f3560e01c80638a054ac2146029578063ffae15ba14603c575b5f80fd5b3480156033575f80fd5b50603a6056565b005b60426058565b604051604d91906075565b60405180910390f35b565b5f34905090565b5f819050919050565b606f81605f565b82525050565b5f60208201905060865f8301846068565b9291505056fea2646970667358221220b890ede9d2428faac28aa986d319e37a797e3b8f4daee4504a5960fc2d16025d64736f6c637828302e382e32352d646576656c6f702e323032342e322e31372b636f6d6d69742e65356165643266330059",
            "opcodes": "PUSH1 0x80 PUSH1 0x40 MSTORE CALLVALUE DUP1 ISZERO PUSH2 0xF JUMPI PUSH0 DUP1 REVERT JUMPDEST POP PUSH1 0xE8 DUP1 PUSH2 0x1C PUSH0 CODECOPY PUSH0 RETURN INVALID PUSH1 0x80 PUSH1 0x40 MSTORE PUSH1 0x4 CALLDATASIZE LT PUSH1 0x25 JUMPI PUSH0 CALLDATALOAD PUSH1 0xE0 SHR DUP1 PUSH4 0x8A054AC2 EQ PUSH1 0x29 JUMPI DUP1 PUSH4 0xFFAE15BA EQ PUSH1 0x3C JUMPI JUMPDEST PUSH0 DUP1 REVERT JUMPDEST CALLVALUE DUP1 ISZERO PUSH1 0x33 JUMPI PUSH0 DUP1 REVERT JUMPDEST POP PUSH1 0x3A PUSH1 0x56 JUMP JUMPDEST STOP JUMPDEST PUSH1 0x42 PUSH1 0x58 JUMP JUMPDEST PUSH1 0x40 MLOAD PUSH1 0x4D SWAP2 SWAP1 PUSH1 0x75 JUMP JUMPDEST PUSH1 0x40 MLOAD DUP1 SWAP2 SUB SWAP1 RETURN JUMPDEST JUMP JUMPDEST PUSH0 CALLVALUE SWAP1 POP SWAP1 JUMP JUMPDEST PUSH0 DUP2 SWAP1 POP SWAP2 SWAP1 POP JUMP JUMPDEST PUSH1 0x6F DUP2 PUSH1 0x5F JUMP JUMPDEST DUP3 MSTORE POP POP JUMP JUMPDEST PUSH0 PUSH1 0x20 DUP3 ADD SWAP1 POP PUSH1 0x86 PUSH0 DUP4 ADD DUP5 PUSH1 0x68 JUMP JUMPDEST SWAP3 SWAP2 POP POP JUMP INVALID LOG2 PUSH5 0x6970667358 0x22 SLT KECCAK256 0xB8 SWAP1 0xED 0xE9 0xD2 TIMESTAMP DUP16 0xAA 0xC2 DUP11 0xA9 DUP7 0xD3 NOT 0xE3 PUSH27 0x797E3B8F4DAEE4504A5960FC2D16025D64736F6C637828302E382E ORIGIN CALLDATALOAD 0x2D PUSH5 0x6576656C6F PUSH17 0x2E323032342E322E31372B636F6D6D6974 0x2E PUSH6 0x356165643266 CALLER STOP MSIZE ",
            "sourceMap": "68:127:0:-:0;;;;;;;;;;;;;;;;;;;"
          },
          "gasEstimates": {
            "creation": {
              "codeDepositCost": "46400",
              "executionCost": "97",
              "totalCost": "46497"
            },
            "external": {
              "d()": "121",
              "e()": "307"
            }
          }
        },
        "metadata": "{\"compiler\":{\"version\":\"0.8.25-develop.2024.2.17+commit.e5aed2f3\"},\"language\":\"Solidity\",\"output\":{\"abi\":[{\"inputs\":[],\"name\":\"d\",\"outputs\":[],\"stateMutability\":\"nonpayable\",\"type\":\"function\"},{\"inputs\":[],\"name\":\"e\",\"outputs\":[{\"internalType\":\"uint256\",\"name\":\"\",\"type\":\"uint256\"}],\"stateMutability\":\"payable\",\"type\":\"function\"}],\"devdoc\":{\"kind\":\"dev\",\"methods\":{},\"version\":1},\"userdoc\":{\"kind\":\"user\",\"methods\":{},\"version\":1}},\"settings\":{\"compilationTarget\":{\"contract.sol\":\"C\"},\"evmVersion\":\"shanghai\",\"libraries\":{},\"metadata\":{\"bytecodeHash\":\"ipfs\"},\"optimizer\":{\"enabled\":false,\"runs\":200},\"remappings\":[]},\"sources\":{\"contract.sol\":{\"keccak256\":\"0x196e5e31eada104e53dd4980715477cb9541297aec84b15aadbb1982db5787f8\",\"license\":\"GPL-3.0\",\"urls\":[\"bzz-raw://19e5672b2a50e7180f5917c28df9c7bd157721a2021407c992ef619cea3c6df4\",\"dweb:/ipfs/QmesPBbnh7rqY8qpD8BwZqWomp47P5fYze619X6Qm3xTAq\"]}},\"version\":1}",
        "userdoc": {
          "kind": "user",
          "methods": {},
          "version": 1
        }
      }
    }
  },
  "errors": [
    {
      "component": "general",
      "errorCode": "3805",
      "formattedMessage": "Warning: This is a pre-release compiler version, please do not use it in production.\n\n",
      "message": "This is a pre-release compiler version, please do not use it in production.",
      "severity": "warning",
      "type": "Warning"
    }
  ],
  "sources": {
    "contract.sol": {
      "ast": {
        "absolutePath": "contract.sol",
        "exportedSymbols": {
          "C": [
            15
          ]
        },
        "id": 16,
        "license": "GPL-3.0",
        "nodeType": "SourceUnit",
        "nodes": [
          {
            "id": 1,
            "literals": [
              "solidity",
              ">=",
              "0.7",
              ".0",
              "<",
              "0.9",
              ".0"
            ],
            "nodeType": "PragmaDirective",
            "src": "36:31:0"
          },
          {
            "abstract": false,
            "baseContracts": [],
            "canonicalName": "C",
            "contractDependencies": [],
            "contractKind": "contract",
            "fullyImplemented": true,
            "id": 15,
            "linearizedBaseContracts": [
              15
            ],
            "name": "C",
            "nameLocation": "77:1:0",
            "nodeType": "ContractDefinition",
            "nodes": [
              {
                "body": {
                  "id": 4,
                  "nodeType": "Block",
                  "src": "105:7:0",
                  "statements": []
                },
                "functionSelector": "8a054ac2",
                "id": 5,
                "implemented": true,
                "kind": "function",
                "modifiers": [],
                "name": "d",
                "nameLocation": "94:1:0",
                "nodeType": "FunctionDefinition",
                "parameters": {
                  "id": 2,
                  "nodeType": "ParameterList",
                  "parameters": [],
                  "src": "95:2:0"
                },
                "returnParameters": {
                  "id": 3,
                  "nodeType": "ParameterList",
                  "parameters": [],
                  "src": "105:0:0"
                },
                "scope": 15,
                "src": "85:27:0",
                "stateMutability": "nonpayable",
                "virtual": false,
                "visibility": "public"
              },
              {
                "body": {
                  "id": 13,
                  "nodeType": "Block",
                  "src": "160:33:0",
                  "statements": [
                    {
                      "expression": {
                        "expression": {
                          "id": 10,
                          "name": "msg",
                          "nodeType": "Identifier",
                          "overloadedDeclarations": [],
                          "referencedDeclaration": -15,
                          "src": "177:3:0",
                          "typeDescriptions": {
                            "typeIdentifier": "t_magic_message",
                            "typeString": "msg"
                          }
                        },
                        "id": 11,
                        "isConstant": false,
                        "isLValue": false,
                        "isPure": false,
                        "lValueRequested": false,
                        "memberLocation": "181:5:0",
                        "memberName": "value",
                        "nodeType": "MemberAccess",
                        "src": "177:9:0",
                        "typeDescriptions": {
                          "typeIdentifier": "t_uint256",
                          "typeString": "uint256"
                        }
                      },
                      "functionReturnParameters": 9,
                      "id": 12,
                      "nodeType": "Return",
                      "src": "170:16:0"
                    }
                  ]
                },
                "functionSelector": "ffae15ba",
                "id": 14,
                "implemented": true,
                "kind": "function",
                "modifiers": [],
                "name": "e",
                "nameLocation": "126:1:0",
                "nodeType": "FunctionDefinition",
                "parameters": {
                  "id": 6,
                  "nodeType": "ParameterList",
                  "parameters": [],
                  "src": "127:2:0"
                },
                "returnParameters": {
                  "id": 9,
                  "nodeType": "ParameterList",
                  "parameters": [
                    {
                      "constant": false,
                      "id": 8,
                      "mutability": "mutable",
                      "name": "",
                      "nameLocation": "-1:-1:-1",
                      "nodeType": "VariableDeclaration",
                      "scope": 14,
                      "src": "154:4:0",
                      "stateVariable": false,
                      "storageLocation": "default",
                      "typeDescriptions": {
                        "typeIdentifier": "t_uint256",
                        "typeString": "uint256"
                      },
                      "typeName": {
                        "id": 7,
                        "name": "uint",
                        "nodeType": "ElementaryTypeName",
                        "src": "154:4:0",
                        "typeDescriptions": {
                          "typeIdentifier": "t_uint256",
                          "typeString": "uint256"
                        }
                      },
                      "visibility": "internal"
                    }
                  ],
                  "src": "153:6:0"
                },
                "scope": 15,
                "src": "117:76:0",
                "stateMutability": "payable",
                "virtual": false,
                "visibility": "public"
              }
            ],
            "scope": 16,
            "src": "68:127:0",
            "usedErrors": [],
            "usedEvents": []
          }
        ],
        "src": "36:159:0"
      },
      "id": 0
    }
  }
}
```
