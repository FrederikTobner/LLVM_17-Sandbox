set(LLVM_LINK_COMPONENTS
  Support
  )

add_tinylang_tool(tinylang
  Driver.cpp
  )

target_link_libraries(tinylang
  PRIVATE
  tinylangBasic
  tinylangLexer
  tinylangParser
  tinylangSema
  )

  
set_target_properties(tinylang PROPERTIES LINKER_LANGUAGE CXX)