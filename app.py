from flask import Flask, render_template, jsonify
import time
import serial
import serial.tools.list_ports

app = Flask(__name__)
serialInst = serial.Serial()
serialInst.baudrate = 9600

def get_available_ports():
    """Get list of available serial ports."""
    available_ports = serial.tools.list_ports.comports()
    ports_list = [
        {
            "device": port.device,
            "name": f"{port.device} - {port.description}",
        }
        for port in available_ports
    ]
    return ports_list

@app.route("/")
def home():
    ports = get_available_ports()
    return render_template("index.html", ports=ports)

@app.route("/command/<port>/<action>")
def send_command(port, action):
    """Send command to Arduino via serial port."""
    try:
        # Close existing connection if open
        if serialInst.is_open:
            serialInst.close()
        
        # Open the selected port
        serialInst.port = port
        serialInst.open()
        time.sleep(2) # Wait for the connection to establish
        
        # Send the command
        if action in ["ON", "OFF", "BLINK"]:
            serialInst.write((action + "\n").encode())
            return jsonify({"status": "success", "message": f"Command {action} sent to {port}"})
        else:
            return jsonify({"status": "error", "message": "Invalid command"}), 400
    
    except serial.SerialException as e:
        return jsonify({"status": "error", "message": str(e)}), 500
    except Exception as e:
        return jsonify({"status": "error", "message": str(e)}), 500
    finally:
        if serialInst.is_open:
            serialInst.close()

if __name__ == "__main__":
    app.run(debug=False)
