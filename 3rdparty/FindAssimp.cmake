# assimp
CPMAddPackage(
        NAME assimp
        GITHUB_REPOSITORY assimp/assimp
        GIT_TAG v5.2.5
        OPTIONS
        "ASSIMP_WARNINGS_AS_ERRORS OFF"
        "ASSIMP_BUILD_TESTS Off"
        "ASSIMP_BUILD_EXAMPLES Off"
        "ASSIMP_BUILD_DOCS Off"
        "ASSIMP_INSTALL_PDB Off"
)