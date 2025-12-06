# Asset system ideas

ingest is done via game files, we extract ziff (Z-axis IFF) to more pallatable formats
(GLTF? capnp?) which we can deal with much easier. Additionally, during import, source assets are de-duplicated automatically.

# schema

each supported object type has its own capnp schema which describes it

# ingest

ingest should either be via a disc image (ISO file) or a folder dump.