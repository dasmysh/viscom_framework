# VISCOM Framework

[![Build Status](https://travis-ci.com/dasmysh/viscom_framework.svg?branch=develop)](https://travis-ci.com/dasmysh/viscom_framework)

This framework is a modification of the [VISCOM Framework](https://github.com/viscom-ulm/viscom_framework) with enhanced functionality and tailored for my personal preferences.

It has serialization support due to [Cereal](https://github.com/USCiLab/cereal) and uses [glBinding](https://github.com/cginternals/glbinding) as OpenGL binding
Due to the latter both mesh rendering classes (`MeshRenderable`, `AnimMeshRenderable`) defined in the original core framework are not usable.
Otherwise it just has some convenient extensions to the original framework like animations, some post processing effects and OpenGL object wrapper classes.
