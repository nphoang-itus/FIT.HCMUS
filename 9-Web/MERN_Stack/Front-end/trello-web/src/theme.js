import { createTheme } from '@mui/material/styles';
import { red } from '@mui/material/colors';
import { light } from '@mui/material/styles/createPalette';

// Create a theme instance.
const theme = createTheme({
  cssVariables: true,
  palette: {
    mode: 'light',
    primary: {
      main: '#0ad0d4ff',
    },
    secondary: {
      main: '#19857b',
    },
    error: {
      main: red.A400,
    },
    text: {
      secondary: red[500]
    }
  },
});

export default theme;