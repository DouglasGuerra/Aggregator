
(cl:in-package :asdf)

(defsystem "shared_files-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "drive" :depends-on ("_package_drive"))
    (:file "_package_drive" :depends-on ("_package"))
  ))