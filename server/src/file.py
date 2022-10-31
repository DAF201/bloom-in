from flask import request, Flask, send_file
import os
import platform

config = {
    "host": "0.0.0.0",
    "port": 5232,
    "params": ["file_name", "file_size", "sha256"],
    "max_file_size": 104857600,  # 100mb
    "download_path": (__file__.split(os.path.basename(__file__))[0] + "download\\"),
}


app = Flask(__name__)

if not os.path.isdir(config["download_path"]):
    os.system("mkdir " + config["download_path"])


@app.route("/upload", methods=["post"])
def upload():
    try:
        args = request.args
        file_name = args["file_name"]
        file_size = int(args["file_size"])
        file = request.files["file"]

        if (
            file_size > config["max_file_size"]
            or file.content_length > config["max_file_size"]
        ):
            print("file over size")
            return {"status": -1}, 200
        if platform.system() != "Linux":
            file.save(config["download_path"] + "/" + file_name)
        else:
            file.save(file_name)
        return {"status": 1}, 200

    except Exception as e:
        print(e)
        return {"status": 0}, 200


@app.route("/download", methods=["get"])
def download():
    try:
        args = request.args
        file_name = args["file_name"]
        if platform.system() == "Linux":
            return (
                send_file(file_name, as_attachment=True),
                200,
            )
        else:
            return (
                send_file(
                    config["download_path"] + "/" + file_name, as_attachment=True
                ),
                200,
            )

    except Exception as e:
        print(e)
    return {"status": 0}, 200

@app.route("/debug", methods=["get","post"])
def debug():
    return request.method
app.run(config["host"], config["port"])
