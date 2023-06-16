; Auto-generated. Do not edit!


(cl:in-package speedimu-msg)


;//! \htmlinclude imuspeed.msg.html

(cl:defclass <imuspeed> (roslisp-msg-protocol:ros-message)
  ((a
    :reader a
    :initarg :a
    :type cl:float
    :initform 0.0))
)

(cl:defclass imuspeed (<imuspeed>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <imuspeed>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'imuspeed)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name speedimu-msg:<imuspeed> is deprecated: use speedimu-msg:imuspeed instead.")))

(cl:ensure-generic-function 'a-val :lambda-list '(m))
(cl:defmethod a-val ((m <imuspeed>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader speedimu-msg:a-val is deprecated.  Use speedimu-msg:a instead.")
  (a m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <imuspeed>) ostream)
  "Serializes a message object of type '<imuspeed>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'a))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <imuspeed>) istream)
  "Deserializes a message object of type '<imuspeed>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'a) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<imuspeed>)))
  "Returns string type for a message object of type '<imuspeed>"
  "speedimu/imuspeed")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'imuspeed)))
  "Returns string type for a message object of type 'imuspeed"
  "speedimu/imuspeed")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<imuspeed>)))
  "Returns md5sum for a message object of type '<imuspeed>"
  "3a9a8ccf1ae2be3477477819c0d93b4e")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'imuspeed)))
  "Returns md5sum for a message object of type 'imuspeed"
  "3a9a8ccf1ae2be3477477819c0d93b4e")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<imuspeed>)))
  "Returns full string definition for message of type '<imuspeed>"
  (cl:format cl:nil "float32 a~%~%~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'imuspeed)))
  "Returns full string definition for message of type 'imuspeed"
  (cl:format cl:nil "float32 a~%~%~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <imuspeed>))
  (cl:+ 0
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <imuspeed>))
  "Converts a ROS message object to a list"
  (cl:list 'imuspeed
    (cl:cons ':a (a msg))
))
