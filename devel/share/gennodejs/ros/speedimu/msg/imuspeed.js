// Auto-generated. Do not edit!

// (in-package speedimu.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class imuspeed {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.a = null;
    }
    else {
      if (initObj.hasOwnProperty('a')) {
        this.a = initObj.a
      }
      else {
        this.a = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type imuspeed
    // Serialize message field [a]
    bufferOffset = _serializer.float32(obj.a, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type imuspeed
    let len;
    let data = new imuspeed(null);
    // Deserialize message field [a]
    data.a = _deserializer.float32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 4;
  }

  static datatype() {
    // Returns string type for a message object
    return 'speedimu/imuspeed';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '3a9a8ccf1ae2be3477477819c0d93b4e';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float32 a
    
    
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new imuspeed(null);
    if (msg.a !== undefined) {
      resolved.a = msg.a;
    }
    else {
      resolved.a = 0.0
    }

    return resolved;
    }
};

module.exports = imuspeed;
