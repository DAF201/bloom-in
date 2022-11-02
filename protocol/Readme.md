# bloom-in protocol

```
# init protocol
bloom-in protocol V* <channel>*<channel> <id>*<id> BLOOM_IN

# message/control protocol
bloom-in * <no>*<no><channel>*<channel><id>*<id><target>*<target><data>*<data>BLOOM_IN

# exit protocol
bloom-in exit V* <exit><id>*<id><exit> BLOOM_IN
```

### init protocol

To start the connection, the client need to send a start message to server with its channel(token) and its id, then the server will register to pool and start forwarding to client. Otherwise, the servier will close the connection

```
# init protocol
bloom-in protocol V* <channel>*<channel> <id>*<id> BLOOM_IN

[bloom-in protocol]
protocol head

[V*]
protocol version, for example, V0.0.1, does not have any meaning, just symbolically add to protocol for fun

[<channel>*<channel>]
channel(token), where the messages were sent to, max length 16 characters, edit in client's config.config

[<id>*<id>]
user id, to identify a client, edit in client's config.config

[BLOOM_IN]
protocol tail
```
### message/control protocol

Message and command carriage protocol, sady it does not has any encryption and it is plain text

```
# message/control protocol
bloom-in * <no>*<no><channel>*<channel><id>*<id><target>*<target><data>*<data>BLOOM_IN

[bloom-in]
protocol head

[*]
single char type identifier, possible value = {p, e, f, d}, there is another identifier 'h' which is local

'p': print
'e': execute
'f': file
'd': download

[<no>*<no>]
status code, express the current progress.
'p' and 'e': always -1
'f': {0: file upload request, 1: file upload success, -1: file upload fail, 2: file transportation finished, clean up request}

example: test01 want to upload a file to test02
command 1(test01 to test02): ...<no>0<no>... (request to upload a file)
#test02 do something
command 2(test02 to test01): ...<no>1/-1<no>... (file download success or fail)
#test01 do something
command 3(test01 to test02): ...<no>2<no>... (clean up)

'e': {0: file download request, 1: file upload success, -1: file upload fail, 2: file transportation finished, clean up request}

example: test01 want to download a file from test02
command 1(test01 to test02): ...<no>0<no>... (request to download a file)
#test02 do something
command 2(test02 to test01): ...<no>1/-1<no>... (file upload success or fail)
#test01 do something
command 3(test01 to test02): ...<no>2<no>... (clean up)

[<channel>*<channel>]
where the messages being sent to. Target can receive your messages/commands if and only if you and target are at the same channel

[<data>*<data>]
base64 data chunk, max size 1024 (oversize message will be chopped into 1024 chars packages and send out)

[BLOOM_IN]
protocol tail
```  

### exit protocol

enter exit to exit

```
# exit protocol
bloom-in exit V* <exit><id>*<id><exit> BLOOM_IN

[bloom-in exit]
protocol head

[V*]
protocol version

[<exit><id>*<id><exit>]
protocol body with client id

[BLOOM_IN]
protocol tail
```
