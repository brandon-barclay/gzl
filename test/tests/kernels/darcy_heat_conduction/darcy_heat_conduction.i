[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 100
  ny = 100
  xmax = 0.304
  ymax = 0.0257
[]

[Variables]
  [temperature]
  []
[]

[Kernels]
  [darcy_temperature]
    type = ADDarcyHeatConduction
    variable = temperature
  []
[]

[Materials]
  [fluid]
    type = ADGenericConstantMaterial
    prop_names = "thermal_conductivity"
    prop_values = "23"
  []
[]

[BCs]
  [inflow]
    type = ADDirichletBC
    variable = temperature
    boundary = left
    value = 350
  []
  [outflow]
    type = ADDirichletBC
    variable = temperature
    boundary = right
    value = 300
  []
[]

[Problem]
  type = FEProblem
  coord_type = RZ
  rz_coord_axis = X
  []

  [Executioner]
    type = Steady
    solve_type = NEWTON
    petsc_options_iname = '-pc_type'
    petsc_options_value = 'hypre'
  []

  [Outputs]
    exodus = true
  []
