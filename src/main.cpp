#include <libsolidity/interface/StandardCompiler.h>
#include <libsolutil/JSON.h>

#include <boost/algorithm/string/replace.hpp>

#include <iostream>

int main(int, char*[])
{
	std::string contract = R"(
// SPDX-License-Identifier: GPL-3.0
pragma solidity >=0.7.0 <0.9.0;
contract C {
    function d() public {
    }
    function e() public payable returns (uint) {
        return msg.value;
    }
}
)";
	// escaping some sensible characters.
	boost::replace_all(contract, "\n", "\\n");
	boost::replace_all(contract, "\"", "\\\"");

	// standard json input & output format is described here:
	// https://docs.soliditylang.org/en/latest/using-the-compiler.html#compiler-input-and-output-json-description
	std::string input = R"(
	{
		"language": "Solidity",
		"sources": {
			"contract.sol": {
				"content": ")"
						+ contract + R"("
			}
		},
		"settings": {
			"outputSelection": {
				"contract.sol": {
					"C": [ "abi", "devdoc", "userdoc", "evm.bytecode", "evm.assembly", "evm.gasEstimates", "metadata" ],
					"": [ "ast" ]
				}
			}
		}
	}
	)";

	solidity::frontend::StandardCompiler compiler;
	std::string output = compiler.compile(input);

  solidity::Json outputJson;
	solidity::util::jsonParseStrict(output, outputJson);
	std::cout << solidity::util::jsonPrettyPrint(outputJson) << std::endl;

	return 0;
}
