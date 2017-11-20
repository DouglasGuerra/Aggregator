; Auto-generated. Do not edit!


(cl:in-package shared_files-msg)


;//! \htmlinclude position.msg.html

(cl:defclass <position> (roslisp-msg-protocol:ros-message)
  ((found
    :reader found
    :initarg :found
    :type cl:fixnum
    :initform 0)
   (position
    :reader position
    :initarg :position
    :type cl:fixnum
    :initform 0)
   (direction
    :reader direction
    :initarg :direction
    :type cl:fixnum
    :initform 0)
   (rotation_enable
    :reader rotation_enable
    :initarg :rotation_enable
    :type cl:fixnum
    :initform 0)
   (rotation_direction
    :reader rotation_direction
    :initarg :rotation_direction
    :type cl:fixnum
    :initform 0)
   (angle
    :reader angle
    :initarg :angle
    :type cl:float
    :initform 0.0))
)

(cl:defclass position (<position>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <position>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'position)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name shared_files-msg:<position> is deprecated: use shared_files-msg:position instead.")))

(cl:ensure-generic-function 'found-val :lambda-list '(m))
(cl:defmethod found-val ((m <position>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader shared_files-msg:found-val is deprecated.  Use shared_files-msg:found instead.")
  (found m))

(cl:ensure-generic-function 'position-val :lambda-list '(m))
(cl:defmethod position-val ((m <position>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader shared_files-msg:position-val is deprecated.  Use shared_files-msg:position instead.")
  (position m))

(cl:ensure-generic-function 'direction-val :lambda-list '(m))
(cl:defmethod direction-val ((m <position>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader shared_files-msg:direction-val is deprecated.  Use shared_files-msg:direction instead.")
  (direction m))

(cl:ensure-generic-function 'rotation_enable-val :lambda-list '(m))
(cl:defmethod rotation_enable-val ((m <position>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader shared_files-msg:rotation_enable-val is deprecated.  Use shared_files-msg:rotation_enable instead.")
  (rotation_enable m))

(cl:ensure-generic-function 'rotation_direction-val :lambda-list '(m))
(cl:defmethod rotation_direction-val ((m <position>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader shared_files-msg:rotation_direction-val is deprecated.  Use shared_files-msg:rotation_direction instead.")
  (rotation_direction m))

(cl:ensure-generic-function 'angle-val :lambda-list '(m))
(cl:defmethod angle-val ((m <position>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader shared_files-msg:angle-val is deprecated.  Use shared_files-msg:angle instead.")
  (angle m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <position>) ostream)
  "Serializes a message object of type '<position>"
  (cl:let* ((signed (cl:slot-value msg 'found)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'position)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'direction)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'rotation_enable)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'rotation_direction)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'angle))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <position>) istream)
  "Deserializes a message object of type '<position>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'found) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'position) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'direction) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'rotation_enable) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'rotation_direction) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'angle) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<position>)))
  "Returns string type for a message object of type '<position>"
  "shared_files/position")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'position)))
  "Returns string type for a message object of type 'position"
  "shared_files/position")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<position>)))
  "Returns md5sum for a message object of type '<position>"
  "6f5868ec9e98907eb04314775bd5fcdc")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'position)))
  "Returns md5sum for a message object of type 'position"
  "6f5868ec9e98907eb04314775bd5fcdc")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<position>)))
  "Returns full string definition for message of type '<position>"
  (cl:format cl:nil "# The values represent if we are to the left, right, or center in the arena~%# ~%# Found tells us if we have found our object, if not we need to rotate~%# 	1 = found object, so read position and direction variables to know if we need to move~%#	0 = not found object so rotate robot either clockwise or counter-clockwise~%#~%# Position tells us where we are => left, right or center of the arena~%#	-1 = left~%#	0 = center~%#	1 = right~%#~%# Direction tells us which direction we need to move => left or right~%#	-1 = left~%#	0 = stop moving and go forward, we are too close to the dump_site and we don't want to hit~%#	1 = right~%#~%# Rotation_enable tells us if we are centered and need to begin worrying about rotation~%#	1 = centered, we need to orient ourselves~%#	0 = not centered, don't worry about rotation~%#~%# Rotation_direction tells us the direction we need to rotate ~%#	-1 = counter-clockwise~%#	0 = parallel to collecto bin, don't need to rotate anymore~%#	1 = clockwise~%#~%# angle represents the angle deviation from being in parallel to the collector bin~%~%int8 found~%int8 position~%int8 direction~%int8 rotation_enable~%int8 rotation_direction~%float32 angle~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'position)))
  "Returns full string definition for message of type 'position"
  (cl:format cl:nil "# The values represent if we are to the left, right, or center in the arena~%# ~%# Found tells us if we have found our object, if not we need to rotate~%# 	1 = found object, so read position and direction variables to know if we need to move~%#	0 = not found object so rotate robot either clockwise or counter-clockwise~%#~%# Position tells us where we are => left, right or center of the arena~%#	-1 = left~%#	0 = center~%#	1 = right~%#~%# Direction tells us which direction we need to move => left or right~%#	-1 = left~%#	0 = stop moving and go forward, we are too close to the dump_site and we don't want to hit~%#	1 = right~%#~%# Rotation_enable tells us if we are centered and need to begin worrying about rotation~%#	1 = centered, we need to orient ourselves~%#	0 = not centered, don't worry about rotation~%#~%# Rotation_direction tells us the direction we need to rotate ~%#	-1 = counter-clockwise~%#	0 = parallel to collecto bin, don't need to rotate anymore~%#	1 = clockwise~%#~%# angle represents the angle deviation from being in parallel to the collector bin~%~%int8 found~%int8 position~%int8 direction~%int8 rotation_enable~%int8 rotation_direction~%float32 angle~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <position>))
  (cl:+ 0
     1
     1
     1
     1
     1
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <position>))
  "Converts a ROS message object to a list"
  (cl:list 'position
    (cl:cons ':found (found msg))
    (cl:cons ':position (position msg))
    (cl:cons ':direction (direction msg))
    (cl:cons ':rotation_enable (rotation_enable msg))
    (cl:cons ':rotation_direction (rotation_direction msg))
    (cl:cons ':angle (angle msg))
))
