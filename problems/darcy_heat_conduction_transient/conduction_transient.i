[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 20
  ny = 20
  xmax = 0.304
  ymax = 0.0257
[]

[Variables]
  [temperature]
    initial_condition = 300 # at time < 0, before the solve starts
  []
[]

[Kernels]
  [steady]
    type = ADDarcyHeatConduction
    variable = temperature
  []
  [transient]
    type = ADHeatConductionTimeDerivative
    variable = temperature
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
    type = HeatConductionOutflow
    variable = temperature
    boundary = right
    value = 300
  []
[]

[Materials]
  [steel]
    type = ADGenericConstantMaterial
    prop_names = "thermal_conductivity specific_heat density"
    prop_values = "18 0.466 8000"
  []
[]

[Problem]
  type = FEProblem
  coord_type = RZ
  rz_coord_axis = X
[]

[Executioner]
  type = Transient
  steady_state_detection = true
  num_steps = 18
  solve_type = NEWTON
  petsc_options_iname = '-pc_type'
  petsc_options_value = 'hypre'
[]

[Outputs]
  exodus = true
[]
