/* tcp.h
   Mathieu Stefani, 05 novembre 2015
   
   TCP
*/

#pragma once

#include "flags.h"
#include "prototype.h"
#include <memory>

namespace Net {

namespace Tcp {

class Peer;
class Transport;

enum class Options : uint64_t {
    None                 = 0,
    NoDelay              = 1,
    Linger               = NoDelay << 1,
    FastOpen             = Linger << 1,
    QuickAck             = FastOpen << 1,
    ReuseAddr            = QuickAck << 1,
    ReverseLookup        = ReuseAddr << 1,
    InstallSignalHandler = ReverseLookup << 1
};

DECLARE_FLAGS_OPERATORS(Options)

class Handler : private Prototype<Handler> {
public:
    friend class Transport;

    Handler();
    ~Handler();

    virtual void onInput(const char *buffer, size_t len, const std::shared_ptr<Tcp::Peer>& peer) = 0;

    virtual void onConnection(const std::shared_ptr<Tcp::Peer>& peer);
    virtual void onDisconnection(const std::shared_ptr<Tcp::Peer>& peer);

protected:
    Transport *transport() {
        if (!transport_)
            throw std::logic_error("Orphaned handler");
        return transport_;
     }

private:
    void associateTransport(Transport* transport);
    Transport *transport_;
};

} // namespace Tcp

} // namespace Net
