config = {
    "port": 4215,
    "ip": "0.0.0.0",
    "exit_command": "a2dff2049c95fc45de4a6601177db8cdc55d81e8d6506a1771f4d2108854f3a6a81a8ab28f0b3bbc3a46455a4067168773d942de3e502e2d1c22514d976127e8"
}

HEADER = b'bloom-in protocol V\d\.\d.\d <t>\w{0,16}<t> <i>\w{0,16}<i> BLOOM_IN$'

COMMAND = b'bloom-in \w <t>\w{0,16}<t>(<i>\w{0,16}<i>)?<d>\w{0,65535}<d>\s?BLOOM_IN$'

COMMAND_POOL = []