; Auto-generated. Do not edit!


(cl:in-package shared_files-msg)


;//! \htmlinclude drive.msg.html

(cl:defclass <drive> (roslisp-msg-protocol:ros-message)
  ((direction
    :reader direction
    :initarg :direction
    :type cl:integer
    :initform 0)
   (speed
    :reader speed
    :initarg :speed
    :type cl:integer
    :initform 0))
)

(cl:defclass drive (<drive>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <drive>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'drive)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name shared_files-msg:<drive> is deprecated: use shared_files-msg:drive instead.")))

(cl:ensure-generic-function 'direction-val :lambda-list '(m))
(cl:defmethod direction-val ((m <drive>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader shared_files-msg:direction-val is deprecated.  Use shared_files-msg:direction instead.")
  (direction m))

(cl:ensure-generic-function 'speed-val :lambda-list '(m))
(cl:defmethod speed-val ((m <drive>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader shared_files-msg:speed-val is deprecated.  Use shared_files-msg:speed instead.")
  (speed m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <drive>) ostream)
  "Serializes a message object of type '<drive>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'direction)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'direction)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'direction)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'direction)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'speed)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'speed)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'speed)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'speed)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <drive>) istream)
  "Deserializes a message object of type '<drive>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'direction)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'direction)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'direction)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'direction)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'speed)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'speed)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'speed)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'speed)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<drive>)))
  "Returns string type for a message object of type '<drive>"
  "shared_files/drive")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'drive)))
  "Returns string type for a message object of type 'drive"
  "shared_files/drive")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<drive>)))
  "Returns md5sum for a message object of type '<drive>"
  "89726c303325757051a3ce7b2bc535e7")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'drive)))
  "Returns md5sum for a message object of type 'drive"
  "89726c303325757051a3ce7b2bc535e7")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<drive>)))
  "Returns full string definition for message of type '<drive>"
  (cl:format cl:nil "uint32 direction~%uint32 speed~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'drive)))
  "Returns full string definition for message of type 'drive"
  (cl:format cl:nil "uint32 direction~%uint32 speed~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <drive>))
  (cl:+ 0
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <drive>))
  "Converts a ROS message object to a list"
  (cl:list 'drive
    (cl:cons ':direction (direction msg))
    (cl:cons ':speed (speed msg))
))
