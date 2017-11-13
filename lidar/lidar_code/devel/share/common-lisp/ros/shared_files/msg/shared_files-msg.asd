
(cl:in-package :asdf)

(defsystem "shared_files-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "position" :depends-on ("_package_position"))
    (:file "_package_position" :depends-on ("_package"))
    (:file "angle_rotation" :depends-on ("_package_angle_rotation"))
    (:file "_package_angle_rotation" :depends-on ("_package"))
  ))