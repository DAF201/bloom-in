config = {
    "port": 4215,
    "ip": "0.0.0.0",
    "exit_command": "a2dff2049c95fc45de4a6601177db8cdc55d81e8d6506a1771f4d2108854f3a6a81a8ab28f0b3bbc3a46455a4067168773d942de3e502e2d1c22514d976127e8"
}

HEADER = b'bloom-in protocol V\d\.\d.\d <channel>\w{0,16}<channel> <id>\w{0,16}<id> BLOOM_IN$'

COMMAND = b'bloom-in \w <channel>\w{0,16}<channel><id>\w{0,16}<id><target>\w{0,16}<target><data>(?:[A-Za-z0-9+\/]{4})*(?:[A-Za-z0-9+\/]{4}|[A-Za-z0-9+\/]{3}=|[A-Za-z0-9+\/]{2}={2})<data>BLOOM_IN$'

EXIT = b'bloom-in exit V\d\.\d.\d <exit><id>\w{0,16}<id><exit> BLOOM_IN$'

COMMAND_POOL = []
