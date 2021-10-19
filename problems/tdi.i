[Mesh]
  type = GeneratedMesh
  dim = 3
  nx = 100
  ny = 10
  nz = 10
  xmax = 0.304 # Length of test chamber
  ymax = 0.0257 # Test chamber radius
  zmax = 0.0257
[]

[Variables]
  [temperature]
    initial_condition = 300 # Start at room temperature
  []
[]

[Kernels]
  [heat_conduction]
    type = ADHeatConduction
    variable = temperature
  []
  [heat_conduction_time_derivative]
    type = ADHeatConductionTimeDerivative
    variable = temperature
  []
[]

[BCs]
  [inlet_temperature]
    type = DirichletBC
    variable = temperature
    boundary = left
    value = 350 # (K)
  []
  [outlet_temperature]
    type = DirichletBC
    variable = temperature
    boundary = right
    value = 300 # (K)
  []
[]

[Materials]
  [steel]
    type = ADGenericConstantMaterial
    prop_names = 'thermal_conductivity specific_heat density'
    prop_values = '0.7 0.466 8000' # W/m*K, J/kg-K, kg/m^3 @ 296K
  []
[]

[Problem]
  type = FEProblem
  #coord_type = RZ
  #rz_coord_axis = X
[]

[Executioner]
  type = Transient
  steady_state_detection = true
  steady_state_tolerance = 3e-7
  num_steps = 1000
  solve_type = NEWTON
  #petsc_options_iname = '-pc_type -pc_hypre_type'
  #petsc_options_value = 'hypre boomeramg'
[]

[Outputs]
  exodus = true
[]