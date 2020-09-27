{
  "targets": [
    {
      "target_name": "addon",
      "sources": [ "addon.cc" ],
      'include_dirs': ["./","/opt/rrdtool-1.7.2/include/"],
      'link_settings': {
        'libraries': [
            '-lrrd',
          ],
        'library_dirs': [
            '/opt/rrdtool-1.7.2/lib/',
          ],
      },
    }
  ]
}
