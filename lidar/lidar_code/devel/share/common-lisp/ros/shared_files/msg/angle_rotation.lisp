; Auto-generated. Do not edit!


(cl:in-package shared_files-msg)


;//! \htmlinclude angle_rotation.msg.html

(cl:defclass <angle_rotation> (roslisp-msg-protocol:ros-message)
  ((enable
    :reader enable
    :initarg :enable
    :type cl:fixnum
    :initform 0)
   (direction
    :reader direction
    :initarg :direction
    :type cl:fixnum
    :initform 0)
   (angle
    :reader angle
    :initarg :angle
    :type cl:float
    :initform 0.0))
)

(cl:defclass angle_rotation (<angle_rotation>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <angle_rotation>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'angle_rotation)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name shared_files-msg:<angle_rotation> is deprecated: use shared_files-msg:angle_rotation instead.")))

(cl:ensure-generic-function 'enable-val :lambda-list '(m))
(cl:defmethod enable-val ((m <angle_rotation>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader shared_files-msg:enable-val is deprecated.  Use shared_files-msg:enable instead.")
  (enable m))

(cl:ensure-generic-function 'direction-val :lambda-list '(m))
(cl:defmethod direction-val ((m <angle_rotation>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader shared_files-msg:direction-val is deprecated.  Use shared_files-msg:direction instead.")
  (direction m))

(cl:ensure-generic-function 'angle-val :lambda-list '(m))
(cl:defmethod angle-val ((m <angle_rotation>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader shared_files-msg:angle-val is deprecated.  Use shared_files-msg:angle instead.")
  (angle m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <angle_rotation>) ostream)
  "Serializes a message object of type '<angle_rotation>"
  (cl:let* ((signed (cl:slot-value msg 'enable)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'direction)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'angle))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <angle_rotation>) istream)
  "Deserializes a message object of type '<angle_rotation>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'enable) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'direction) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'angle) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<angle_rotation>)))
  "Returns string type for a message object of type '<angle_rotation>"
  "shared_files/angle_rotation")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'angle_rotation)))
  "Returns string type for a message object of type 'angle_rotation"
  "shared_files/angle_rotation")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<angle_rotation>)))
  "Returns md5sum for a message object of type '<angle_rotation>"
  "70e02d19e6f4d7979bc0aff4297d83f6")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'angle_rotation)))
  "Returns md5sum for a message object of type 'angle_rotation"
  "70e02d19e6f4d7979bc0aff4297d83f6")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<angle_rotation>)))
  "Returns full string definition for message of type '<angle_rotation>"
  (cl:format cl:nil "# These value are sent when the robot is already centered, and we need to orient the robot to~%# have it parallel to the dump site~%#~%# Enable tells us if we have finished centering the robot and we can worry about rotation~%#~%# Direction tells us whether to rotate clockwise or counter-clockwise~%#	-1 = counter-clockwise~%#	1 = clockwise~%#	0 = in parallel, no need to rotate~%#~%# Angle represents, in degrees, how much we need to rotate to be in parallel to the dump site~%~%int8 enable~%int8 direction 	~%float32 angle~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'angle_rotation)))
  "Returns full string definition for message of type 'angle_rotation"
  (cl:format cl:nil "# These value are sent when the robot is already centered, and we need to orient the robot to~%# have it parallel to the dump site~%#~%# Enable tells us if we have finished centering the robot and we can worry about rotation~%#~%# Direction tells us whether to rotate clockwise or counter-clockwise~%#	-1 = counter-clockwise~%#	1 = clockwise~%#	0 = in parallel, no need to rotate~%#~%# Angle represents, in degrees, how much we need to rotate to be in parallel to the dump site~%~%int8 enable~%int8 direction 	~%float32 angle~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <angle_rotation>))
  (cl:+ 0
     1
     1
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <angle_rotation>))
  "Converts a ROS message object to a list"
  (cl:list 'angle_rotation
    (cl:cons ':enable (enable msg))
    (cl:cons ':direction (direction msg))
    (cl:cons ':angle (angle msg))
))
