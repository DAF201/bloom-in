config = {
    "port": 4215,
    "ip": "0.0.0.0"
}

HEADER = b'bloom-in protocol V\d\.\d.\d <channel>\w{0,16}<channel> <id>\w{0,16}<id> BLOOM_IN$'

COMMAND = b'bloom-in \w <channel>\w{0,16}<channel><id>\w{0,16}<id><target>\w{0,16}<target><data>(?:[A-Za-z0-9+\/]{4})*(?:[A-Za-z0-9+\/]{4}|[A-Za-z0-9+\/]{3}=|[A-Za-z0-9+\/]{2}={2})<data>BLOOM_IN$'

EXIT = b'bloom-in exit V\d\.\d.\d <exit><id>\w{0,16}<id><exit> BLOOM_IN$'

COMMAND_POOL = []
