# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from shared_files/angle_rotation.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct


class angle_rotation(genpy.Message):
  _md5sum = "70e02d19e6f4d7979bc0aff4297d83f6"
  _type = "shared_files/angle_rotation"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """# These value are sent when the robot is already centered, and we need to orient the robot to
# have it parallel to the dump site
#
# Enable tells us if we have finished centering the robot and we can worry about rotation
#
# Direction tells us whether to rotate clockwise or counter-clockwise
#	-1 = counter-clockwise
#	1 = clockwise
#	0 = in parallel, no need to rotate
#
# Angle represents, in degrees, how much we need to rotate to be in parallel to the dump site

int8 enable
int8 direction 	
float32 angle
"""
  __slots__ = ['enable','direction','angle']
  _slot_types = ['int8','int8','float32']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       enable,direction,angle

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(angle_rotation, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.enable is None:
        self.enable = 0
      if self.direction is None:
        self.direction = 0
      if self.angle is None:
        self.angle = 0.
    else:
      self.enable = 0
      self.direction = 0
      self.angle = 0.

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    :param buff: buffer, ``StringIO``
    """
    try:
      _x = self
      buff.write(_struct_2bf.pack(_x.enable, _x.direction, _x.angle))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      end = 0
      _x = self
      start = end
      end += 6
      (_x.enable, _x.direction, _x.angle,) = _struct_2bf.unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    :param buff: buffer, ``StringIO``
    :param numpy: numpy python module
    """
    try:
      _x = self
      buff.write(_struct_2bf.pack(_x.enable, _x.direction, _x.angle))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      end = 0
      _x = self
      start = end
      end += 6
      (_x.enable, _x.direction, _x.angle,) = _struct_2bf.unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
_struct_2bf = struct.Struct("<2bf")
