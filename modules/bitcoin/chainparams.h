// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2021 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_CHAINPARAMS_H
#define BITCOIN_CHAINPARAMS_H

#include <kernel/chainparams.h> // IWYU pragma: export

#include <memory>

class ArgsManager;

/**
 * CBaseChainParams defines the base parameters (shared between bitcoin-cli and bitcoind)
 * of a given instance of the Bitcoin system.
 */
class CBaseChainParams
{
public:
    const std::string& DataDir() const { return strDataDir; }
    uint16_t RPCPort() const { return m_rpc_port; }
    uint16_t OnionServiceTargetPort() const { return m_onion_service_target_port; }

    CBaseChainParams() = delete;
    CBaseChainParams(const std::string& data_dir, uint16_t rpc_port, uint16_t onion_service_target_port)
        : m_rpc_port(rpc_port), m_onion_service_target_port(onion_service_target_port), strDataDir(data_dir) {}

private:
    const uint16_t m_rpc_port;
    const uint16_t m_onion_service_target_port;
    std::string strDataDir;
};

/**
 * Creates and returns a std::unique_ptr<CChainParams> of the chosen chain.
 */
std::unique_ptr<const CChainParams> CreateChainParams(const ArgsManager& args, const ChainType chain);

/**
 * Return the currently selected parameters. This won't change after app
 * startup, except for unit tests.
 */
const CChainParams &Params();

/**
 * Sets the params returned by Params() to those for the given chain type.
 */
void SelectParams(const ChainType chain);

#endif // BITCOIN_CHAINPARAMS_H
