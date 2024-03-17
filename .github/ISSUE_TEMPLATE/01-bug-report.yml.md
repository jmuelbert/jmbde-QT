name: "Bug Report"
description: Report an issue or possible bug
title: "[Bug]:  "
labels: ["bug", "triage"]
assignees:
  - jmuelbert
body:
  - type: markdown
    attributes:
      value: |
        Thank you for taking the time to file a bug report! Please fill out this form as completely as possible.

        ✅ I am using the **latest versions of jmbde-QT**.
  - type: input
    id: jmbde-version
    attributes:
      label: What version of `jmbde-QT` are you using?
      placeholder: 0.0.0
    validations:
      required: true
  - type: input
    id: Qt Version
    attributes:
      label: What version of `Qt` are you using?
      placeholder: 6.5.2
    validations:
      required: true
  - type: input
    id: os
    attributes:
      label: What operating system are you using?
      placeholder: Mac, Windows, Linux
    validations:
      required: true
  - type: textarea
    id: bug-description
    attributes:
      label: Describe the Bug
      description: A clear and concise description of what the bug is.
    validations:
      required: true
  - type: textarea
    id: logs
    attributes:
      label: Relevant log output
      description: Please copy and paste any relevant log output. This will be automatically formatted into code, so no need for backticks.
      render: shell
  - type: checkboxes
    id: will-pr
    attributes:
      label: Participation
      options:
        - label: I am willing to submit a pull request for this issue.
          required: false
  - type: checkboxes
    id: terms
    attributes:
      label: Code of Conduct
      description: By submitting this issue, you agree to follow our [Code of Conduct](https://github.com/jmuelbert/jmbde-QT/blob/main/CODE_OF_CONDUCT.md)
      options:
        - label: I agree to follow this project's Code of Conduct
          required: true